#include "pch.h"
#include "SecondLayer.h"
#include "util.h"
#include "DBManager.h"
#include "InfoLayer.h"

USING_NS_CC;



bool SecondLayer::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
		return false;

	this->setContentSize(Size(WINSIZE_WIDTH, WINSIZE_HEIGHT));

	auto showInfo = MenuItemImage::create("showInfo.png", "showInfoPress.png",
										  CC_CALLBACK_1(SecondLayer::showInfoMenuEvent, this));

	showInfo->setPosition(Point(WINSIZE_WIDTH / 2, WINSIZE_HEIGHT/6 * 4));
	m_ShowInfoMenu = Menu::create(showInfo, NULL);
	m_ShowInfoMenu->setPosition(Point::ZERO);
	this->addChild(m_ShowInfoMenu, 1);

	auto updateInfo = MenuItemImage::create("update.png", "updatePress.png",
										  CC_CALLBACK_1(SecondLayer::updateMenuEvent, this));

	updateInfo->setPosition(Point(WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 6 * 3));
	m_UpdateMenu = Menu::create(updateInfo, NULL);
	m_UpdateMenu->setPosition(Point::ZERO);
	this->addChild(m_UpdateMenu, 1);

	auto searchInfo = MenuItemImage::create("search.png", "searchPress.png",
										  CC_CALLBACK_1(SecondLayer::searchMenuEvent, this));

	searchInfo->setPosition(Point(WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 6 * 2));
	m_SearchMenu = Menu::create(searchInfo, NULL);
	m_SearchMenu->setPosition(Point::ZERO);
	this->addChild(m_SearchMenu, 1);

	auto backMenu = MenuItemImage::create("back.png", "back.png",
											CC_CALLBACK_1(SecondLayer::backMenuEvent, this));

	backMenu->setScale(0.7f);
	backMenu->setPosition(Point(WINSIZE_WIDTH  - backMenu->getContentSize().width/2, WINSIZE_HEIGHT / 8));

	m_BackMenu = Menu::create(backMenu, NULL);
	m_BackMenu->setPosition(Point::ZERO);
	this->addChild(m_BackMenu, 1);

	//infolayer 등록
	m_InfoLayer = InfoLayer::create();
	this->addChild(m_InfoLayer,2);
	m_InfoLayer->setPosition(Point::ZERO);
	m_InfoLayer->setVisible(false);

	return true;
}

void SecondLayer::showInfoMenuEvent(Ref* pSender)
{
	//1. 내가 들은 과목 목록
	
	m_InfoLayer->setVisible(true);
	
   
}

void SecondLayer::updateMenuEvent(Ref* pSender)
{

}

void SecondLayer::searchMenuEvent(Ref* pSender)
{

}

void SecondLayer::backMenuEvent(cocos2d::Ref* psender)
{
	setVisible(false);
}
