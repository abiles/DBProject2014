#pragma once
#include "cocos2d.h"

class InfoLayer;

class SecondLayer : public cocos2d::LayerColor
{
public:
	virtual bool init();

	void		 showInfoMenuEvent(Ref* pSender);
	void		 updateMenuEvent(Ref* pSender);
	void		 searchMenuEvent(Ref* pSender);

	CREATE_FUNC(SecondLayer);
private:
	cocos2d::Menu*		  m_ShowInfoMenu = nullptr;
	cocos2d::Menu*		  m_UpdateMenu = nullptr;
	cocos2d::Menu*		  m_SearchMenu = nullptr;
	InfoLayer*			  m_InfoLayer = nullptr;

};