#include "pch.h"
#include <Windows.h>
#include <iostream>

#include "DBManager.h"

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
	
	return true;
}

void DBManager::freeHandles()
{
	if (m_HStmt) SQLFreeHandle(SQL_HANDLE_STMT,m_HStmt);
	if (m_HDbc) SQLDisconnect(m_HDbc);
	if (m_HDbc) SQLFreeHandle(SQL_HANDLE_DBC, m_HDbc);
	if (m_HEnv) SQLFreeHandle(SQL_HANDLE_ENV, m_HEnv);
}


