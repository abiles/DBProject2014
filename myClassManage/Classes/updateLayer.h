#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class EditMyCourseLayer;
class EditContentsLayer;
class UpdateLayer : public cocos2d::LayerColor
{
public:
	virtual bool init();

	void		 updateMyCourseMenuEvent(cocos2d::Ref* pSender);
	void		 updateContentMenuEvent(cocos2d::Ref* pSender);
	void		 backMenuEvent(cocos2d::Ref* psender);

	CREATE_FUNC(UpdateLayer);

private:
	cocos2d::Menu*					 m_UpdateMyCourseMenu = nullptr;
	cocos2d::Menu*					 m_UpdateContentMenu = nullptr;
	cocos2d::Menu*					 m_BackMenu = nullptr;
	EditMyCourseLayer*				 m_EditMyCourseLayer = nullptr;
	EditContentsLayer*				 m_EditContentsLayer = nullptr;
	

};