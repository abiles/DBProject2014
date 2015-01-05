#pragma once
#include "cocos2d.h"


class InfoLayer : public cocos2d::LayerColor
{
public:
	virtual bool init();
	void		 showAllCourseEvent(cocos2d::Ref* sender);
	void		 showMyCourseEvent(cocos2d::Ref* sender);
	void		 backEvent(cocos2d::Ref* sender);
	void		 allCourseBackEvent(cocos2d::Ref* sender);




	CREATE_FUNC(InfoLayer);
private:
	cocos2d::Menu*					 m_AllCourseMenu = nullptr;
	cocos2d::Menu*					 m_MyCourseMenu = nullptr;
	cocos2d::Menu*					 m_BackMenu = nullptr;
	cocos2d::Menu*					 m_AllCourseBackMenu = nullptr;
	std::vector<cocos2d::Label*>     m_AllCourseLabel;

};