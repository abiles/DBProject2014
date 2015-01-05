#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class EditMyCourseLayer : public cocos2d::LayerColor, public cocos2d::ui::EditBoxDelegate
{
public:
	virtual bool init();

	void		 addBoxInit();
	void		 deleteBoxInit();
	void		 backMenuEvent(cocos2d::Ref* psender);


	CREATE_FUNC(EditMyCourseLayer);

private:
	virtual void					 editBoxReturn(cocos2d::ui::EditBox* editBox);

	cocos2d::ui::EditBox*			 m_AddCourse = nullptr;
	cocos2d::ui::EditBox*			 m_DeleteCourse = nullptr;
	cocos2d::Menu*					 m_BackMenu = nullptr;


};