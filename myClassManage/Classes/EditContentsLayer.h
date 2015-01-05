#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <sql.h>
#include <sqlext.h>

class EditContentsLayer : public cocos2d::LayerColor, public cocos2d::ui::EditBoxDelegate
{
public:
	virtual bool init();
	void		 updateMyCourseMenuEvent(cocos2d::Ref* pSender);
	void		 updateContentMenuEvent(cocos2d::Ref* pSender);
	void		 backMenuEvent(cocos2d::Ref* psender);
	void		 addMenuEvent(cocos2d::Ref* psender);
	void		 deleteMenuEvent(cocos2d::Ref* psender);


	CREATE_FUNC(EditContentsLayer);

private:
	virtual void					 editBoxReturn(cocos2d::ui::EditBox* editBox);

	void		 initAddBox();
	void		 initDeleteBox();
	void		 initAddMenu();
	void		 initDeleteMenu();
	void         initBackMenu();

	cocos2d::ui::EditBox*			 m_AddCourseId = nullptr;
	cocos2d::ui::EditBox*			 m_AddCourseWeek = nullptr;
	cocos2d::ui::EditBox*			 m_AddCourseIdx = nullptr;
	cocos2d::ui::EditBox*			 m_AddCourseSubstance = nullptr;

	cocos2d::ui::EditBox*			 m_DeleteCourseId = nullptr;
	cocos2d::ui::EditBox*			 m_DeleteCourseWeek = nullptr;
	cocos2d::ui::EditBox*			 m_DeleteCourseIdx = nullptr;

	SQLWCHAR						 m_AddId[100];
	SQLWCHAR						 m_AddWeek[100];
	SQLWCHAR						 m_AddIdx[100];
	SQLWCHAR						 m_AddSub[100];

	SQLWCHAR						 m_DeleteId[100];
	SQLWCHAR						 m_DeleteWeek[100];
	SQLWCHAR						 m_DeleteIdx[100];


	cocos2d::Menu*					 m_BackMenu = nullptr;
	cocos2d::Menu*					 m_AddMenu = nullptr;
	cocos2d::Menu*					 m_DeleteMenu = nullptr;

};