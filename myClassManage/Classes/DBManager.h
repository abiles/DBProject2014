/*

className : DBManager.h
활용		  : DB연결이나 DB 사용하는 부분을 맡음
만든 날짜  : 2015-01-04


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
	bool			  loadUserCourseInfo(const SQLWCHAR* inputId, OUT std::string* courseInfo);
	bool			  getContentsByCourseId(const SQLWCHAR* courseId, OUT std::string* courseInfo);
	bool			  getInfoBySearchInput(const SQLWCHAR* searchInput, OUT std::string* courseInfo);
	bool			  updateMyCourse(const SQLWCHAR* courseId);
	bool			  deleteMyCourse(const SQLWCHAR* courseId);
	bool			  addContents(const SQLWCHAR* courseId, const SQLWCHAR* courseWeek,
								  const SQLWCHAR* courseIdx, const SQLWCHAR* courseSub);
	bool			  deleteContents(const SQLWCHAR* courseId, const SQLWCHAR* courseWeek,
									 const SQLWCHAR* courseIdx);
	void			  setUserId(const SQLWCHAR* userId);
	SQLWCHAR*		  getUserId();

	

private:
	static DBManager* m_DBManager;
	SQLHENV		      m_HEnv = nullptr;
	SQLHDBC		      m_HDbc = nullptr;
	SQLHSTMT	      m_HStmt = nullptr;
	SQLWCHAR		  m_UserId[100];

	DBManager();
	~DBManager();
};   


