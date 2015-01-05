#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <sql.h>
#include <sqlext.h>

class InfoLayer : public cocos2d::LayerColor, public cocos2d::ui::EditBoxDelegate
{
public:
	virtual bool init();
	void		 showAllCourseEvent(cocos2d::Ref* sender);
	void		 showMyCourseEvent(cocos2d::Ref* sender);
	void		 backEvent(cocos2d::Ref* sender);
	void		 allCourseBackEvent(cocos2d::Ref* sender);
	void		 myCourseBackEvent(cocos2d::Ref* sender);
	void		 editBoxBackEvent(cocos2d::Ref* sender);
	void		 createTitle(std::vector<cocos2d::Label*>* labels);
	void		 editBoxInit();




	CREATE_FUNC(InfoLayer);
private:
	virtual void					 editBoxReturn(cocos2d::ui::EditBox* editBox);

	cocos2d::Menu*					 m_AllCourseMenu = nullptr;
	cocos2d::Menu*					 m_MyCourseMenu = nullptr;
	cocos2d::Menu*					 m_BackMenu = nullptr;
	cocos2d::Menu*					 m_AllCourseBackMenu = nullptr;
	cocos2d::Menu*					 m_MyCourseBackMenu = nullptr;
	cocos2d::Menu*					 m_BackEditBox = nullptr;
	cocos2d::ui::EditBox*			 m_ChooseCourse = nullptr;
	SQLWCHAR						 m_CourseId[100];

	std::vector<cocos2d::Label*>     m_AllCourseLabels;
	std::vector<cocos2d::Label*>     m_MyCourseLabels;
	std::vector<cocos2d::Label*>     m_CourseContentsLabels;
};