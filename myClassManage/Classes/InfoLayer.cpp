#include "pch.h"
#include "InfoLayer.h"
#include "util.h"
#include "DBManager.h"
#include <iostream>
#include <sstream>

USING_NS_CC;

bool InfoLayer::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
		return false;

	this->setContentSize(Size(WINSIZE_WIDTH, WINSIZE_HEIGHT));
	m_AllCourseLabel.reserve(30);

	//모든 과목 보기 버튼 
	auto allCourse = MenuItemImage::create("allCourse.png", "allCoursePress.png",
										   CC_CALLBACK_1(InfoLayer::showAllCourseEvent, this));

	allCourse->setPosition(Point(WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 3 * 2));
	m_AllCourseMenu = Menu::create(allCourse, NULL);
	m_AllCourseMenu->setPosition(Point::ZERO);
	this->addChild(m_AllCourseMenu, 1);

	//내가 들은 과목 보기 버튼 
	auto myCourse = MenuItemImage::create("myCourse.png", "myCoursePress.png",
										  CC_CALLBACK_1(InfoLayer::showMyCourseEvent, this));
	myCourse->setPosition(Point(WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 3));
	m_MyCourseMenu = Menu::create(myCourse, NULL);
	m_MyCourseMenu->setPosition(Point::ZERO);
	this->addChild(m_MyCourseMenu, 1);

	//선택 화면에서 뒤로가기 버튼
	auto back = MenuItemImage::create("Back.png", "Back.png",
										  CC_CALLBACK_1(InfoLayer::backEvent, this));
	back->setPosition(Point(WINSIZE_WIDTH - back->getContentSize().width/2, 50));
	m_BackMenu = Menu::create(back, NULL);
	m_BackMenu->setPosition(Point::ZERO);
	this->addChild(m_BackMenu, 1);


	//모든 과목에서 뒤로가기 버튼
	auto allCourseBack = MenuItemImage::create("Back.png", "Back.png",
											   CC_CALLBACK_1(InfoLayer::allCourseBackEvent, this));
	back->setPosition(Point(WINSIZE_WIDTH - back->getContentSize().width / 2, 50));
	m_AllCourseBackMenu = Menu::create(allCourseBack, NULL);
	m_AllCourseBackMenu->setPosition(Point::ZERO);
	this->addChild(m_BackMenu, 1);

	return true;
}

void InfoLayer::showAllCourseEvent(cocos2d::Ref* sender)
{
	//여기서 다른 메뉴들 unvisible로 바꾸고 모든 메뉴 띄우기
	m_AllCourseMenu->setVisible(false);
	m_MyCourseMenu->setVisible(false);
	m_BackMenu->setVisible(false);

	m_AllCourseBackMenu->setVisible(true);

	std::string allCourseInfo;
	GET_DBMANAGER()->loadAllCourseInfo(&allCourseInfo);
	std::stringstream ss(allCourseInfo);
	std::string token;
	int count = 0;
	int spaceY = 30;
	Point firstPos;
	firstPos.x = WINSIZE_WIDTH/2;
	firstPos.y = WINSIZE_HEIGHT - 150;
	
	while (getline(ss, token, ','))
	{
		Label* tmpLabel = Label::createWithSystemFont(token, "Calbri", 25);
		tmpLabel->setAnchorPoint(Point::ZERO);
		this->addChild(tmpLabel);
		m_AllCourseLabel.push_back(tmpLabel);
		
		if (count % 4 == 0)
		{
			firstPos.x = WINSIZE_WIDTH/3;
			firstPos.y -= spaceY;
			tmpLabel->setPosition(firstPos.x, firstPos.y);
		}
		else if (count % 4 == 1)
		{
			firstPos.x += 40;
			tmpLabel->setPosition(firstPos.x, firstPos.y);
		}
		else if (count % 4 == 2)
		{
			firstPos.x += 200;
			tmpLabel->setPosition(firstPos.x, firstPos.y);
		}
		else
		{
			firstPos.x += 100;
			tmpLabel->setPosition(firstPos.x, firstPos.y);
		}
		++count;
	}



}

void InfoLayer::showMyCourseEvent(cocos2d::Ref* sender)
{

}

void InfoLayer::backEvent(cocos2d::Ref* sender)
{
	setVisible(false);
}

void InfoLayer::allCourseBackEvent(cocos2d::Ref* sender)
{
	for (auto pLabel : m_AllCourseLabel)
	{
		pLabel->setVisible(false);
	}

	m_AllCourseBackMenu->setVisible(false);
}
