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


bool DBManager::connectToDB()
{
	setlocale(LC_ALL, "Korean");

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
	{
		return false;
	}
	
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

	wsprintf(query, L"select studentId From student WHERE studentId = %s", inputId);
	SQLExecDirect(m_HStmt, query, SQL_NTS);
	ret = SQLFetch(m_HStmt);


	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		return true;
	else
		return false;
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

	return true;
}


