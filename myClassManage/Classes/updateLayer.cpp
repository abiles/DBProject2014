#include "pch.h"
#include "updateLayer.h"
#include "util.h"
#include "EditMyCourseLayer.h"
#include "EditContentsLayer.h"

USING_NS_CC;

bool UpdateLayer::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
		return false;

	//mycoursemenu
	auto myCourseMenu = MenuItemImage::create("updateMyCourse.png", "updateMyCoursePress.png",
										  CC_CALLBACK_1(UpdateLayer::updateMyCourseMenuEvent, this));

	myCourseMenu->setPosition(Point(WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 3 * 2));
	m_UpdateMyCourseMenu = Menu::create(myCourseMenu, NULL);
	m_UpdateMyCourseMenu->setPosition(Point::ZERO);
	this->addChild(m_UpdateMyCourseMenu, 1);

	//content 메뉴
	auto contentMenu = MenuItemImage::create("updateContents.png", "updateContentsPress.png",
											  CC_CALLBACK_1(UpdateLayer::updateContentMenuEvent, this));

	contentMenu->setPosition(Point(WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 3 ));
	m_UpdateContentMenu = Menu::create(contentMenu, NULL);
	m_UpdateContentMenu->setPosition(Point::ZERO);
	this->addChild(m_UpdateContentMenu, 1);

	//뒤로가기 
	auto backMenu = MenuItemImage::create("back.png", "back.png",
										  CC_CALLBACK_1(UpdateLayer::backMenuEvent, this));

	backMenu->setScale(0.7f);
	backMenu->setPosition(Point(WINSIZE_WIDTH - backMenu->getContentSize().width / 2, WINSIZE_HEIGHT / 8));

	m_BackMenu = Menu::create(backMenu, NULL);
	m_BackMenu->setPosition(Point::ZERO);
	this->addChild(m_BackMenu, 1);
	
	//
	m_EditMyCourseLayer = EditMyCourseLayer::create();
	m_EditMyCourseLayer->setAnchorPoint(Point::ZERO);
	m_EditMyCourseLayer->setPosition(Point::ZERO);
	this->addChild(m_EditMyCourseLayer, 2);
	m_EditMyCourseLayer->setVisible(false);

	//
	m_EditContentsLayer = EditContentsLayer::create();
	m_EditContentsLayer->setAnchorPoint(Point::ZERO);
	m_EditContentsLayer->setPosition(Point::ZERO);
	this->addChild(m_EditContentsLayer, 2);
	m_EditContentsLayer->setVisible(false);

	return true;
}

void UpdateLayer::updateMyCourseMenuEvent(cocos2d::Ref* pSender)
{
	m_EditMyCourseLayer->setVisible(true);
}

void UpdateLayer::updateContentMenuEvent(cocos2d::Ref* pSender)
{
	m_EditContentsLayer->setVisible(true);
}

void UpdateLayer::backMenuEvent(cocos2d::Ref* psender)
{
	
	setVisible(false);
	
}


