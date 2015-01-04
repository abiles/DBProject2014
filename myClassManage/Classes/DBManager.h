/*

className : DBManager.h
Ȱ��		  : DB�����̳� DB ����ϴ� �κ��� ����
���� ��¥  : 2015-01-04


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

