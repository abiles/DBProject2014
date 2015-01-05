#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class UpdateLayer : public cocos2d::LayerColor, public cocos2d::ui::EditBoxDelegate
{
public:
	virtual bool init();

	void		 updateMyCourseMenuEvent(cocos2d::Ref* pSender);
	void		 updateContentMenuEvent(cocos2d::Ref* pSender);

	CREATE_FUNC(UpdateLayer);
private:
	virtual void					 editBoxReturn(cocos2d::ui::EditBox* editBox);

	cocos2d::Menu*					 m_UpdateMyCourseMenu = nullptr;
	cocos2d::Menu*					 m_UpdateContentMenu = nullptr;
	

};