#ifndef __CLASS_MANAGE_H__
#define __CLASS_MANAGE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <sql.h>
#include <sqlext.h>

enum Zorder
{
	ZORDER_START = 0,
	FISRT_LAYER,
	SECOND_LAYER,
	ZORDER_END,
};


class SecondLayer;
class ClassManage : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
public:
	//~ClassManage();
    
    static cocos2d::Scene* createScene();

    virtual bool init();
    void		 menuCloseCallback(cocos2d::Ref* pSender);
	void		 resisterMenuEvent(cocos2d::Ref* pSender);
	void		 firstToSecondMenuEvent(cocos2d::Ref* pSender);
	void		 initLabels();
    
	void		 editBoxInit();
   
    CREATE_FUNC(ClassManage);

private:
	virtual void		  editBoxReturn(cocos2d::ui::EditBox* editBox);

	SQLWCHAR			  m_UserId[100];
	cocos2d::Size		  m_VisibleSize = cocos2d::Size::ZERO;
	cocos2d::ui::EditBox* m_EditBox = nullptr;
	cocos2d::Label*		  m_ResisterInfoLabel = nullptr;
	cocos2d::Label*       m_ResisterResultLabel = nullptr;
	cocos2d::Menu*		  m_ResistrationMenu = nullptr;
	cocos2d::Menu*		  m_FirstToSecondMenu = nullptr;
	SecondLayer*		  m_SecondLayer = nullptr;


};

#endif // __CLASS_MANAGE_H__

