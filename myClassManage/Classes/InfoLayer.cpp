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

	memset(m_CourseId, 0, sizeof(m_CourseId));
	this->setContentSize(Size(WINSIZE_WIDTH, WINSIZE_HEIGHT));
	m_AllCourseLabels.reserve(100);
	m_MyCourseLabels.reserve(100);
	m_CourseContentsLabels.reserve(300);

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
	back->setScale(0.7f);
	back->setPosition(Point(WINSIZE_WIDTH - back->getContentSize().width / 2, WINSIZE_HEIGHT / 8));
	m_BackMenu = Menu::create(back, NULL);
	m_BackMenu->setPosition(Point::ZERO);
	this->addChild(m_BackMenu, 1);
	
	//모든 과목에서 뒤로가기 버튼
	auto allCourseBack = MenuItemImage::create("Back.png", "Back.png",
											   CC_CALLBACK_1(InfoLayer::allCourseBackEvent, this));
	allCourseBack->setScale(0.7f);
	allCourseBack->setPosition(Point(WINSIZE_WIDTH - allCourseBack->getContentSize().width / 2, WINSIZE_HEIGHT / 8));
	m_AllCourseBackMenu = Menu::create(allCourseBack, NULL);
	m_AllCourseBackMenu->setPosition(Point::ZERO);
	this->addChild(m_AllCourseBackMenu, 1);
	m_AllCourseBackMenu->setVisible(false);
	

	//내 과목에서 뒤로가기 버튼
	auto myCourseBack = MenuItemImage::create("Back.png", "Back.png",
											   CC_CALLBACK_1(InfoLayer::myCourseBackEvent, this));
	myCourseBack->setScale(0.7f);
	myCourseBack->setPosition(Point(WINSIZE_WIDTH - myCourseBack->getContentSize().width / 2, WINSIZE_HEIGHT / 8));
	m_MyCourseBackMenu = Menu::create(myCourseBack, NULL);
	m_MyCourseBackMenu->setPosition(Point::ZERO);
	this->addChild(m_MyCourseBackMenu, 1);
	m_MyCourseBackMenu->setVisible(false);

	//과목 선택용 editbox
	m_ChooseCourse = ui::EditBox::create(Size(300, 100), "SpriteToolEditBox.png");
	m_ChooseCourse->setScale(0.5f);
	editBoxInit();
	this->addChild(m_ChooseCourse, 1);
	m_ChooseCourse->setVisible(false);

	//editbox Back
	auto editBack = MenuItemImage::create("Back.png", "Back.png",
											  CC_CALLBACK_1(InfoLayer::editBoxBackEvent, this));
	editBack->setScale(0.7f);
	editBack->setAnchorPoint(Point::ZERO);
	editBack->setPosition(Point(WINSIZE_WIDTH - editBack->getContentSize().width / 1.5, WINSIZE_HEIGHT / 8));
	m_BackEditBox = Menu::create(editBack, NULL);
	m_BackEditBox->setPosition(Point::ZERO);
	this->addChild(m_BackEditBox, 1);
	m_BackEditBox->setVisible(false);


	return true;
}

void InfoLayer::showAllCourseEvent(cocos2d::Ref* sender)
{
	for (auto pLabel : m_AllCourseLabels)
	{
		if (pLabel)
		{
			pLabel->removeFromParent();
		}
	}
	m_AllCourseLabels.clear();
	m_AllCourseLabels.reserve(30);

	//여기서 다른 메뉴들 unvisible로 바꾸고 모든 메뉴 띄우기
	m_AllCourseMenu->setVisible(false);
	m_MyCourseMenu->setVisible(false);
	m_BackMenu->setVisible(false);

	m_AllCourseBackMenu->setVisible(true);
	m_ChooseCourse->setVisible(true);
	createTitle(&m_AllCourseLabels);

	std::string allCourseInfo;
	GET_DBMANAGER()->loadAllCourseInfo(&allCourseInfo);
	std::stringstream ss(allCourseInfo);
	std::string token;
	int count = 0;
	int spaceY = 30;
	Point firstPos;
	firstPos.x = WINSIZE_WIDTH/3;
	firstPos.y = WINSIZE_HEIGHT - 20;

	while (getline(ss, token, ','))
	{
		Label* tmpLabel = Label::createWithSystemFont(token, "noto sans korean bold", 20);
		tmpLabel->setAnchorPoint(Point::ZERO);
		this->addChild(tmpLabel);
		m_AllCourseLabels.push_back(tmpLabel);
		
	}

	for (auto pLabel : m_AllCourseLabels)
	{

		if (count % 4 == 0)
		{
			firstPos.x = WINSIZE_WIDTH / 3;
			firstPos.y -= spaceY;
			pLabel->setPosition(firstPos.x, firstPos.y);
		}
		else if (count % 4 == 1)
		{
			firstPos.x += 40;
			pLabel->setPosition(firstPos.x, firstPos.y);
		}
		else if (count % 4 == 2)
		{
			firstPos.x += 200;
			pLabel->setPosition(firstPos.x, firstPos.y);
		}
		else
		{
			firstPos.x += 100;
			pLabel->setPosition(firstPos.x, firstPos.y);
		}
		++count;
	}

}

void InfoLayer::showMyCourseEvent(cocos2d::Ref* sender)
{
	for (auto pLabel : m_MyCourseLabels)
	{
		if (pLabel)
		{
			pLabel->removeFromParent();
		}
	}
	m_MyCourseLabels.clear();
	m_MyCourseLabels.reserve(30);

	m_BackMenu->setVisible(false);
	m_MyCourseMenu->setVisible(false);
	m_AllCourseMenu->setVisible(false);

	m_ChooseCourse->setVisible(true);
	m_MyCourseBackMenu->setVisible(true);

	createTitle(&m_MyCourseLabels);

	std::string myCourseInfo;
	GET_DBMANAGER()->loadUserCourseInfo(GET_DBMANAGER()->getUserId(), &myCourseInfo);
	std::stringstream ss(myCourseInfo);
	std::string token;
	int count = 0;
	int spaceY = 30;
	Point firstPos;
	firstPos.x = WINSIZE_WIDTH / 3;
	firstPos.y = WINSIZE_HEIGHT - 20;

	while (getline(ss, token, ','))
	{
		Label* tmpLabel = Label::createWithSystemFont(token, "noto sans korean bold", 20);
		tmpLabel->setAnchorPoint(Point::ZERO);
		this->addChild(tmpLabel);
		m_MyCourseLabels.push_back(tmpLabel);
	}

	for (auto pLabel : m_MyCourseLabels)
	{

		if (count % 4 == 0)
		{
			firstPos.x = WINSIZE_WIDTH / 3;
			firstPos.y -= spaceY;
			pLabel->setPosition(firstPos.x, firstPos.y);
		}
		else if (count % 4 == 1)
		{
			firstPos.x += 40;
			pLabel->setPosition(firstPos.x, firstPos.y);
		}
		else if (count % 4 == 2)
		{
			firstPos.x += 200;
			pLabel->setPosition(firstPos.x, firstPos.y);
		}
		else
		{
			firstPos.x += 100;
			pLabel->setPosition(firstPos.x, firstPos.y);
		}
		++count;
	}
}

void InfoLayer::backEvent(cocos2d::Ref* sender)
{
	setVisible(false);
}

void InfoLayer::allCourseBackEvent(cocos2d::Ref* sender)
{
	for (auto pLabel : m_AllCourseLabels)
	{
		pLabel->setVisible(false);
	}

	m_AllCourseBackMenu->setVisible(false);
	m_ChooseCourse->setVisible(false);

	m_BackMenu->setVisible(true);
	m_MyCourseMenu->setVisible(true);
	m_AllCourseMenu->setVisible(true);
}

void InfoLayer::myCourseBackEvent(cocos2d::Ref* sender)
{
	for (auto pLabel : m_MyCourseLabels)
	{
		pLabel->setVisible(false);
	}

	m_MyCourseBackMenu->setVisible(false);
	m_ChooseCourse->setVisible(false);

	m_BackMenu->setVisible(true);
	m_MyCourseMenu->setVisible(true);
	m_AllCourseMenu->setVisible(true);
}

void InfoLayer::createTitle(std::vector<cocos2d::Label*>* labels)
{
	Label* idLabel = Label::createWithSystemFont("ID", "noto sans korean bold", 20);
	Label* courseLabel = Label::createWithSystemFont("Course", "noto sans korean bold", 20);
	Label* yearLabel = Label::createWithSystemFont("Year", "noto sans korean bold", 20);
	Label* semesterLabel = Label::createWithSystemFont("학기", "noto sans korean bold", 20);

	idLabel->setAnchorPoint(Point::ZERO);
	courseLabel->setAnchorPoint(Point::ZERO);
	yearLabel->setAnchorPoint(Point::ZERO);
	semesterLabel->setAnchorPoint(Point::ZERO);

	this->addChild(idLabel);
	this->addChild(courseLabel);
	this->addChild(yearLabel);
	this->addChild(semesterLabel);

	labels->push_back(idLabel);
	labels->push_back(courseLabel);
	labels->push_back(yearLabel);
	labels->push_back(semesterLabel);
}

void InfoLayer::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
	m_BackEditBox->setVisible(true);

	for (auto pLabel : m_MyCourseLabels)
	{
		if (pLabel)
		{
			pLabel->setVisible(false);
		}
	}

	for (auto pLabel : m_AllCourseLabels)
	{
		if (pLabel)
		{
			pLabel->setVisible(false);
		}
	}


	for (auto pLabel : m_CourseContentsLabels)
	{
		if (pLabel)
		{
			pLabel->removeFromParent();
		}
	}
	m_CourseContentsLabels.clear();

	m_AllCourseBackMenu->setVisible(false);
	m_MyCourseBackMenu->setVisible(false);

	//보고싶은 과목의 숫자를 고른거지 
	const char* tmpText = editBox->getText();
	int len = strlen(tmpText);
	MultiByteToWideChar(0, 0, tmpText, len + 1, m_CourseId, len + 1);
	std::string chooseCourseInfo;
	if (GET_DBMANAGER()->getContentsByCourseId(m_CourseId, &chooseCourseInfo))
	{
		std::stringstream ss(chooseCourseInfo);
		std::string token;
		int count = 0;
		int spaceY = 30;
		Point firstPos;
		firstPos.x = WINSIZE_WIDTH / 8;
		firstPos.y = WINSIZE_HEIGHT - 20;

		while (getline(ss, token, ','))
		{
			Label* tmpLabel = Label::createWithSystemFont(token, "noto sans korean bold", 17);
			tmpLabel->setAnchorPoint(Point::ZERO);
			this->addChild(tmpLabel);
			m_CourseContentsLabels.push_back(tmpLabel);
		}

		for (auto pLabel : m_CourseContentsLabels)
		{

			if (count % 3 == 0)
			{
				if (count >= 0 && count < 45)
				{
					firstPos.x = WINSIZE_WIDTH / 8;
				}
				else if (count >= 45 && count < 90)
				{
					firstPos.x = WINSIZE_WIDTH / 8 + 250;
					if (count == 45)
					{
						firstPos.y = WINSIZE_HEIGHT - 20;
					}

				}	
				else
				{
					firstPos.x = WINSIZE_WIDTH / 8 + 500;
					if (count == 90)
					{
						firstPos.y = WINSIZE_HEIGHT - 20;
					}

				}

				firstPos.y -= spaceY;
				pLabel->setPosition(firstPos.x, firstPos.y);
			}
			else if (count % 3 == 1)
			{
				firstPos.x += 35;
				pLabel->setPosition(firstPos.x, firstPos.y);
			}
			else
			{
				firstPos.x += 30;
				float posY = firstPos.y - 25;
				pLabel->setPosition(firstPos.x, posY);
			}
		
			++count;
		}
	}
	else
	{
		//nodata 
	}
}

void InfoLayer::editBoxInit()
{
	m_ChooseCourse->setPosition(Point(WINSIZE_WIDTH - m_ChooseCourse->getContentSize().width / 2, WINSIZE_HEIGHT / 2));
	m_ChooseCourse->setFont("noto sans korean bold", 24);
	m_ChooseCourse->setFontColor(Color3B::YELLOW);
	m_ChooseCourse->setPlaceHolder("과목 선택");
	m_ChooseCourse->setPlaceholderFontName("noto sans korean bold");
	m_ChooseCourse->setPlaceholderFontColor(Color3B::YELLOW);
	m_ChooseCourse->setMaxLength(6);
	m_ChooseCourse->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_ChooseCourse->setDelegate(this);
}

void InfoLayer::editBoxBackEvent(cocos2d::Ref* sender)
{
	for (auto pLabel : m_CourseContentsLabels)
	{
		if (pLabel)
		{
			pLabel->setVisible(false);
		}
	}

	m_ChooseCourse->setVisible(false);
	m_BackEditBox->setVisible(false);
	m_AllCourseMenu->setVisible(true);
	m_MyCourseMenu->setVisible(true);
	m_BackMenu->setVisible(true);
}

