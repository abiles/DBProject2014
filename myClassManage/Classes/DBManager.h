/*

className : DBManager.h
활용		  : DB연결이나 DB 사용하는 부분을 맡음
만든 날짜  : 2015-01-04


*/
#include <sql.h>
#include <sqlext.h>

class DBManager
{
public:
	DBManager();
	~DBManager();

	bool			connectToDB();
	void			freeHandles();

private:
	SQLHENV		m_HEnv = nullptr;
	SQLHDBC		m_HDbc = nullptr;
	SQLHSTMT	m_HStmt = nullptr;
};

