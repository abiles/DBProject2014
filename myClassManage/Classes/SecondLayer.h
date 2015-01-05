#pragma once
#include "cocos2d.h"

class InfoLayer;
class SearchLayer;
class SecondLayer : public cocos2d::LayerColor
{
public:
	virtual bool init();

	void		 showInfoMenuEvent(cocos2d::Ref* pSender);
	void		 updateMenuEvent(cocos2d::Ref* pSender);
	void		 searchMenuEvent(cocos2d::Ref* pSender);
	void		 backMenuEvent(cocos2d::Ref* psender);

	CREATE_FUNC(SecondLayer);
private:
	cocos2d::Menu*		  m_ShowInfoMenu = nullptr;
	cocos2d::Menu*		  m_UpdateMenu = nullptr;
	cocos2d::Menu*		  m_SearchMenu = nullptr;
	cocos2d::Menu*		  m_BackMenu = nullptr;
	InfoLayer*			  m_InfoLayer = nullptr;
	SearchLayer*		  m_SearchLayer = nullptr;

};