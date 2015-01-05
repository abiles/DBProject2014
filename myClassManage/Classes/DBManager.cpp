#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "DBManager.h"

DBManager* DBManager::m_DBManager = nullptr;

DBManager::DBManager()
{

}

DBManager::~DBManager()
{
	freeHandles();
}


DBManager* DBManager::getInstance()
{
	if (m_DBManager == nullptr)
	{
		m_DBManager = new DBManager();
	}

	return m_DBManager;
}

void DBManager::releaseInstance()
{
	if (m_DBManager != nullptr)
	{
		delete m_DBManager;
		m_DBManager = nullptr;
	}
}


bool DBManager::connectToDB()
{
	setlocale(LC_ALL, "Korean");
	memset(m_UserId, 0, sizeof(m_UserId));

	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_HEnv) != SQL_SUCCESS)
		return false;
	

	if (SQLSetEnvAttr(m_HEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,
		SQL_IS_INTEGER) != SQL_SUCCESS)
		return false;
	

	if (SQLAllocHandle(SQL_HANDLE_DBC, m_HEnv, &m_HDbc) != SQL_SUCCESS)
		return false;
	

	if (SQLConnect(m_HDbc, (SQLWCHAR*)L"DBFinalProject", SQL_NTS,
					 (SQLWCHAR*)L"root", SQL_NTS,
					 (SQLWCHAR*)L"dpqksrp1", SQL_NTS) != SQL_SUCCESS)
		return false;
	
	
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_HDbc, &m_HStmt) != SQL_SUCCESS)
		return false;

	SQLWCHAR query[300] = { 0, };
	wsprintf(query, L"use classproject");
	SQLExecDirect(m_HStmt, query, SQL_NTS);
	
	return true;
}

void DBManager::freeHandles()
{
	if (m_HStmt) SQLFreeHandle(SQL_HANDLE_STMT,m_HStmt);
	if (m_HDbc) SQLDisconnect(m_HDbc);
	if (m_HDbc) SQLFreeHandle(SQL_HANDLE_DBC, m_HDbc);
	if (m_HEnv) SQLFreeHandle(SQL_HANDLE_ENV, m_HEnv);
}

bool DBManager::isInputIDExist(const SQLWCHAR* inputId)
{
	if (inputId == nullptr)
		return false;
	int ret = 0;
	SQLWCHAR query[300] = { 0, };

	SQLHSTMT hStmt = nullptr;
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_HDbc, &hStmt) != SQL_SUCCESS)
		return false;

	wsprintf(query, L"select studentId From student WHERE studentId = %s", inputId);
	SQLExecDirect(hStmt, query, SQL_NTS);
	ret = SQLFetch(hStmt);

	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		return true;
	else
		return false;
}


bool DBManager::resisterNewUserId(const SQLWCHAR* inputId)
{
	if (!inputId)
		return false;

	int ret = 0;
	SQLWCHAR query[300] = { 0, };

	wsprintf(query, L"INSERT INTO student(studentId) Values(%s)", inputId);
	ret = SQLExecDirect(m_HStmt, query, SQL_NTS);

	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		return true;
	else
		return false;
}

bool DBManager::loadAllCourseInfo(OUT std::string* courseInfo)
{
	int ret = 0;
	SQLWCHAR query[300] = { 0, };

	SQLHSTMT hStmt = nullptr;
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_HDbc, &hStmt) != SQL_SUCCESS)
		return false;
	
	wsprintf(query, L"SELECT * FROM course");
	ret = SQLExecDirect(hStmt, query, SQL_NTS);
	if (ret == SQL_NO_DATA || ret == SQL_ERROR)
		return false;
	ret = SQLFetch(hStmt);

	while (ret == SQL_SUCCESS_WITH_INFO || ret == SQL_SUCCESS)
	{

		SQLWCHAR courseName[200] = { 0, };
		SQLLEN id = 0, iIdLen = 0, year = 0, iYearLen = 0, semester = 0, iSemesterLen = 0, iCourseLen = 0;

		if (SQLGetData(hStmt, 1, SQL_C_ULONG, &id, 0, &iIdLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 2, SQL_C_WCHAR, courseName, sizeof(courseName), &iCourseLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 3, SQL_C_ULONG, &year, 0, &iYearLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 4, SQL_C_ULONG, &semester, 0, &iSemesterLen) == SQL_ERROR)
			return false;

		std::string idStr = std::to_string(id);
		*courseInfo += idStr;
		*courseInfo += ',';

		char ch[260];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP, 0, courseName, -1, ch, 260, &DefChar, NULL);
		std::string courseString(ch);
		*courseInfo += courseString;
		*courseInfo += ',';

		std::string yearStr = std::to_string(year);
		*courseInfo += yearStr;
		*courseInfo += ',';

		std::string semesterStr = std::to_string(semester);
		*courseInfo += semesterStr;
		*courseInfo += ',';

		ret = SQLFetch(hStmt);
	}

	courseInfo->pop_back();

	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	return true;
}

bool DBManager::loadUserCourseInfo(const SQLWCHAR* inputId, OUT std::string* courseInfo)
{
	int ret = 0;
	SQLWCHAR query[300] = { 0, };

	SQLHSTMT hStmt = nullptr;
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_HDbc, &hStmt) != SQL_SUCCESS)
		return false;
		
	wsprintf(query, L"SELECT * FROM course WHERE courseId IN (SELECT course_courseId FROM student_resister_for_course WHERE student_studentId = %s)", inputId);
	ret = SQLExecDirect(hStmt, query, SQL_NTS);
	if (ret == SQL_NO_DATA || ret == SQL_ERROR)
		return false;

	ret = SQLFetch(hStmt);

	if (ret == SQL_NO_DATA)
		return false;
	
	while (ret == SQL_SUCCESS_WITH_INFO || ret == SQL_SUCCESS)
	{
		SQLWCHAR courseName[200] = { 0, };
		SQLLEN id = 0, iIdLen = 0, year = 0, iYearLen = 0, semester = 0, iSemesterLen = 0, iCourseLen = 0;

		if (SQLGetData(hStmt, 1, SQL_C_ULONG, &id, 0, &iIdLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 2, SQL_C_WCHAR, courseName, sizeof(courseName), &iCourseLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 3, SQL_C_ULONG, &year, 0, &iYearLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 4, SQL_C_ULONG, &semester, 0, &iSemesterLen) == SQL_ERROR)
			return false;

		std::string idStr = std::to_string(id);
		*courseInfo += idStr;
		*courseInfo += ',';

		char ch[260];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP, 0, courseName, -1, ch, 260, &DefChar, NULL);
		std::string courseString(ch);
		*courseInfo += courseString;
		*courseInfo += ',';

		std::string yearStr = std::to_string(year);
		*courseInfo += yearStr;
		*courseInfo += ',';

		std::string semesterStr = std::to_string(semester);
		*courseInfo += semesterStr;
		*courseInfo += ',';

		ret = SQLFetch(hStmt);
	}

	courseInfo->pop_back();

	if (m_HStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	return true;
}

void DBManager::setUserId(const SQLWCHAR* userId)
{
	wsprintf(m_UserId, L"%s", userId);
}

SQLWCHAR* DBManager::getUserId()
{
	return m_UserId;
}

bool DBManager::getContentsByCourseId(const SQLWCHAR* courseId, OUT std::string* courseInfo)
{
	int ret = 0;
	SQLWCHAR query[300] = { 0, };

	SQLHSTMT hStmt = nullptr;
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_HDbc, &hStmt) != SQL_SUCCESS)
		return false;

	wsprintf(query, L"SELECT week, contentsIdx, substance FROM content WHERE Course_CourseId = %s",courseId);
	ret = SQLExecDirect(hStmt, query, SQL_NTS);
	if (ret == SQL_NO_DATA || ret == SQL_ERROR)
		return false;

	ret = SQLFetch(hStmt);

	if (ret == SQL_NO_DATA)
		return false;

	while (ret == SQL_SUCCESS_WITH_INFO || ret == SQL_SUCCESS)
	{
		SQLWCHAR substance[200] = { 0, };
		SQLLEN  week = 0, iWeekLen = 0, idx = 0, iIdxLen = 0, iSubstanceLen = 0;

		if (SQLGetData(hStmt, 1, SQL_C_ULONG, &week, 0, &iWeekLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 2, SQL_C_ULONG, &idx, 0, &iIdxLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 3, SQL_C_WCHAR, substance, sizeof(substance), &iSubstanceLen) == SQL_ERROR)
			return false;

		std::string weekStr = std::to_string(week);
		*courseInfo += weekStr;
		*courseInfo += ',';

		std::string idxStr = std::to_string(idx);
		*courseInfo += idxStr;
		*courseInfo += ',';

		char ch[260];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP, 0, substance, -1, ch, 260, &DefChar, NULL);
		std::string substanceStr(ch);
		*courseInfo += substanceStr;
		*courseInfo += ',';

		ret = SQLFetch(hStmt);
	}

	courseInfo->pop_back();

	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	return true;
}

bool DBManager::getInfoBySearchInput(const SQLWCHAR* searchInput, OUT std::string* courseInfo)
{
	int ret = 0;
	SQLWCHAR query[500] = { 0, };

	SQLHSTMT hStmt = nullptr;
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_HDbc, &hStmt) != SQL_SUCCESS)
		return false;

	wsprintf(query, L"select c.courseName, p.professorName, c.year, c.semester, con.week, con.substance From content con "
			 L"join professor_lecture_course pl ON pl.course_courseId = con.course_courseId "
			 L"join professor p ON pl.Professor_ProfessorId = p.professorId "
			 L"join course c On c.courseId = con.course_courseId "
			 L"where substance like \"%%%s%%\"", searchInput);
	ret = SQLExecDirect(hStmt, query, SQL_NTS);
	if (ret == SQL_NO_DATA || ret == SQL_ERROR)
		return false;

	ret = SQLFetch(hStmt);
	if (ret == SQL_NO_DATA)
		return false;

	while (ret == SQL_SUCCESS_WITH_INFO || ret == SQL_SUCCESS)
	{
		SQLWCHAR courseName[200] = { 0, };
		SQLWCHAR professorName[200] = { 0, };
		SQLWCHAR substance[200] = { 0, };
		SQLLEN  week = 0, iWeekLen = 0, year = 0, iYearLen = 0, semester = 0, iSemesterLen = 0, iCourseNameLen = 0,
				iProfessorNameLen = 0, iSubstanceLen = 0;

		if (SQLGetData(hStmt, 1, SQL_C_WCHAR, &courseName, sizeof(courseName), &iCourseNameLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 2, SQL_C_WCHAR, &professorName, sizeof(professorName), &iProfessorNameLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 3, SQL_C_ULONG, &year, 0, &iYearLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 4, SQL_C_ULONG, &semester, 0, &iSemesterLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 5, SQL_C_ULONG, &week, 0, &iWeekLen) == SQL_ERROR)
			return false;
		if (SQLGetData(hStmt, 6, SQL_C_WCHAR, &substance, sizeof(substance), &iSubstanceLen) == SQL_ERROR)
			return false;


		char ch[260];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP, 0, courseName, -1, ch, 260, &DefChar, NULL);
		std::string courseNameStr(ch);
		*courseInfo += courseNameStr;
		*courseInfo += ',';

		char proName[260];
		char proChar = ' ';
		WideCharToMultiByte(CP_ACP, 0, professorName, -1, proName, 260, &proChar, NULL);
		std::string proNameStr(proName);
		*courseInfo += proNameStr;
		*courseInfo += ',';

		std::string yearStr = std::to_string(year);
		*courseInfo += yearStr;
		*courseInfo += ',';

		std::string semesterStr = std::to_string(semester);
		*courseInfo += semesterStr;
		*courseInfo += ',';

		std::string weekStr = std::to_string(week);
		*courseInfo += weekStr;
		*courseInfo += ',';

		char sub[260];
		char subChar = ' ';
		WideCharToMultiByte(CP_ACP, 0, substance, -1, sub, 260, &subChar, NULL);
		std::string substanceStr(sub);
		*courseInfo += substanceStr;
		*courseInfo += ',';

		ret = SQLFetch(hStmt);
	}

	courseInfo->pop_back();

	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	return true;
}


