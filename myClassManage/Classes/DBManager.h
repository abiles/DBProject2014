/*

className : DBManager.h
Ȱ��		  : DB�����̳� DB ����ϴ� �κ��� ����
���� ��¥  : 2015-01-04


*/
#pragma once

#include <sql.h>
#include <sqlext.h>
#include <string>

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
	bool			  loadAllCourseInfo(OUT std::string* courseInfo);
	bool			  loadUserCourseInfo(const SQLWCHAR* inputId);

	

private:
	static DBManager* m_DBManager;
	SQLHENV		      m_HEnv = nullptr;
	SQLHDBC		      m_HDbc = nullptr;
	SQLHSTMT	      m_HStmt = nullptr;

	DBManager();
	~DBManager();
};   


