/*

className : DBManager.h
활용		  : DB연결이나 DB 사용하는 부분을 맡음
만든 날짜  : 2015-01-04


*/
#pragma once

#include <sql.h>
#include <sqlext.h>

#define GET_DBMANAGER() DBManager::getInstance()

class DBManager
{
public:


	static DBManager* getInstance();
	static void		  releaseInstance();
	
	bool			  connectToDB();
	void			  freeHandles();

	bool			  isInputIDExist(const SQLWCHAR* inputId);
	bool			  resisterNewUserId(const SQLWCHAR* inputId);

	

private:
	static DBManager* m_DBManager;
	SQLHENV		      m_HEnv = nullptr;
	SQLHDBC		      m_HDbc = nullptr;
	SQLHSTMT	      m_HStmt = nullptr;

	DBManager();
	~DBManager();
};   


