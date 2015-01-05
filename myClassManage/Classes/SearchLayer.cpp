#include "pch.h"
#include "SearchLayer.h"
#include "util.h"
#include "DBManager.h"
#include <iostream>
#include <sstream>

USING_NS_CC;


bool SearchLayer::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
		return false;

	m_SearchInfoLabels.reserve(100);
	m_SearchInfoTitleLabels.reserve(100);

	m_ContentsSearchEditBox = ui::EditBox::create(Size(300, 100), "SpriteToolEditBox.png");
	editBoxInit();
	this->addChild(m_ContentsSearchEditBox, 1);


	auto searchBack = MenuItemImage::create("Back.png", "Back.png",
											  CC_CALLBACK_1(SearchLayer::searchBackEvent, this));
	searchBack->setScale(0.7f);
	searchBack->setPosition(Point(WINSIZE_WIDTH - searchBack->getContentSize().width / 2, WINSIZE_HEIGHT / 8));
	m_BackSearchMenu = Menu::create(searchBack, NULL);
	m_BackSearchMenu->setPosition(Point::ZERO);
	this->addChild(m_BackSearchMenu, 1);


	auto afterSearchBack = MenuItemImage::create("Back.png", "Back.png",
											  CC_CALLBACK_1(SearchLayer::afterSearchBackEvent, this));
	afterSearchBack->setScale(0.7f);
	afterSearchBack->setPosition(Point(WINSIZE_WIDTH - afterSearchBack->getContentSize().width / 2, WINSIZE_HEIGHT / 8));
	m_BackAfterSearchMenu = Menu::create(afterSearchBack, NULL);
	m_BackAfterSearchMenu->setPosition(Point::ZERO);
	this->addChild(m_BackAfterSearchMenu, 1);
	m_BackAfterSearchMenu->setVisible(false);


	initTitleLabels();


	return true;
}


void SearchLayer::editBoxInit()
{
	m_ContentsSearchEditBox->setPosition(Point(WINSIZE_WIDTH - m_ContentsSearchEditBox->getContentSize().width/2, WINSIZE_HEIGHT / 2));
	m_ContentsSearchEditBox->setFont("noto sans korean bold", 25);
	m_ContentsSearchEditBox->setFontColor(Color3B::YELLOW);
	m_ContentsSearchEditBox->setPlaceHolder("Input Search Keyword");
	m_ContentsSearchEditBox->setPlaceholderFontName("noto sans korean bold");
	m_ContentsSearchEditBox->setPlaceholderFontColor(Color3B::YELLOW);
	m_ContentsSearchEditBox->setMaxLength(6);
	m_ContentsSearchEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_ContentsSearchEditBox->setDelegate(this);
}

void SearchLayer::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
	visibleTitleLables();

	for (auto pLabels : m_SearchInfoLabels)
	{
		if (pLabels)
		{
			pLabels->removeFromParent();
		}
	}
	m_SearchInfoLabels.clear();

	SQLWCHAR searchInput[100] = { 0, };
	const char* tmpText = editBox->getText();

	int len = strlen(tmpText);
	MultiByteToWideChar(CP_UTF8, 0, tmpText, len + 1, searchInput, len + 1);
	//const char* charForSetText = 
	char tmpMultiChar[100] = { 0, };
	WideCharToMultiByte(CP_ACP, 0, searchInput, -1, tmpMultiChar, 100, 0, 0);
	editBox->setText(tmpMultiChar);
	//editBox->setText();
	std::string searchInfo;

	if (GET_DBMANAGER()->getInfoBySearchInput(searchInput, &searchInfo))
	{
		std::stringstream ss(searchInfo);
		std::string token;
		int count = 0;
		int spaceY = 30;
		Point firstPos;
		firstPos.x = WINSIZE_WIDTH / 10;
		firstPos.y = WINSIZE_HEIGHT - 80;

		while (getline(ss, token, ','))
		{
			Label* tmpLabel = Label::createWithSystemFont(token, "noto sans korean bold", 17);
			tmpLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
			this->addChild(tmpLabel);
			m_SearchInfoLabels.push_back(tmpLabel);
		}

		for (auto pLabels : m_SearchInfoLabels)
		{
			if (count % 6 == 0)
			{
				//과목
				firstPos.x = WINSIZE_WIDTH / 8;
				firstPos.y -= spaceY;
				pLabels->setPosition(firstPos.x, firstPos.y);

			}
			else if (count % 6 == 1)
			{
				//교수
				firstPos.x += 120;
				float posY = firstPos.y - 12;
				pLabels->setPosition(firstPos.x, posY);

			}
			else if (count % 6 == 2)
			{
				//year
				firstPos.x += 70;
				pLabels->setPosition(firstPos.x, firstPos.y);

			}
			else if (count % 6 == 3)
			{
				//학기
				firstPos.x += 50;
				pLabels->setPosition(firstPos.x, firstPos.y);

			}
			else if (count % 6 == 4)
			{
				//주
				firstPos.x += 50;
				pLabels->setPosition(firstPos.x, firstPos.y);

			}
			else
			{
				//내용
				firstPos.x += 120;
				float posY = firstPos.y - 12;
				pLabels->setPosition(firstPos.x, posY);

			}
			count++;

		}
	}
}

void SearchLayer::searchBackEvent(cocos2d::Ref* sender)
{
	setVisible(false);
	unvisibleTitleLables();
	for (auto pLabels : m_SearchInfoLabels)
	{
		if (pLabels)
		{
			pLabels->removeFromParent();
		}
	}
	m_SearchInfoLabels.clear();
}

void SearchLayer::afterSearchBackEvent(cocos2d::Ref* sender)
{
	for (auto pLabels : m_SearchInfoLabels)
	{
		if (pLabels)
		{
			pLabels->removeFromParent();
		}
	}
	m_SearchInfoLabels.clear();

	m_BackAfterSearchMenu->setVisible(false);
	m_BackSearchMenu->setVisible(true);
	m_ContentsSearchEditBox->setVisible(true);
}

void SearchLayer::createTitleLabels()
{
	Label* courseLabel = Label::createWithSystemFont("과목", "noto sans korean bold", 17);
	this->addChild(courseLabel);
	m_SearchInfoTitleLabels.push_back(courseLabel);

	Label* proLabel = Label::createWithSystemFont("교수", "noto sans korean bold", 17);
	this->addChild(proLabel);
	m_SearchInfoTitleLabels.push_back(proLabel);
	
	Label* yearLabel = Label::createWithSystemFont("Year", "noto sans korean bold", 17);
	this->addChild(yearLabel);
	m_SearchInfoTitleLabels.push_back(yearLabel);

	Label* semLabel = Label::createWithSystemFont("학기", "noto sans korean bold", 17);
	this->addChild(semLabel);
	m_SearchInfoTitleLabels.push_back(semLabel);

	Label* weekLabel = Label::createWithSystemFont("Week", "noto sans korean bold", 17);
	this->addChild(weekLabel);
	m_SearchInfoTitleLabels.push_back(weekLabel);

	Label* subLabel = Label::createWithSystemFont("내용", "noto sans korean bold", 17);
	this->addChild(subLabel);
	m_SearchInfoTitleLabels.push_back(subLabel);

}

void SearchLayer::assignTitleLabels()
{
	int count = 0;
	int spaceY = 30;
	Point firstPos;
	firstPos.x = WINSIZE_WIDTH / 10;
	firstPos.y = WINSIZE_HEIGHT - 40;
	for (auto pLabels : m_SearchInfoTitleLabels)
	{
		if (count % 6 == 0)
		{
			//과목
			firstPos.x = WINSIZE_WIDTH / 8;
			firstPos.y -= spaceY;
			pLabels->setPosition(firstPos.x, firstPos.y);

		}
		else if (count % 6 == 1)
		{
			//교수
			firstPos.x += 120;
			float posY = firstPos.y;
			pLabels->setPosition(firstPos.x, posY);

		}
		else if (count % 6 == 2)
		{
			//year
			firstPos.x += 70;
			pLabels->setPosition(firstPos.x, firstPos.y);

		}
		else if (count % 6 == 3)
		{
			//학기
			firstPos.x += 50;
			pLabels->setPosition(firstPos.x, firstPos.y);

		}
		else if (count % 6 == 4)
		{
			//주
			firstPos.x += 50;
			pLabels->setPosition(firstPos.x, firstPos.y);

		}
		else
		{
			//내용
			firstPos.x += 120;
			float posY = firstPos.y;
			pLabels->setPosition(firstPos.x, posY);

		}
		count++;

	}
}

void SearchLayer::unvisibleTitleLables()
{
	for (auto pLabel : m_SearchInfoTitleLabels)
	{
		if (pLabel)
		{
			pLabel->setVisible(false);
		}
	}
}

void SearchLayer::visibleTitleLables()
{
	for (auto pLabel : m_SearchInfoTitleLabels)
	{
		if (pLabel)
		{
			pLabel->setVisible(true);
		}
	}
}

void SearchLayer::initTitleLabels()
{
	createTitleLabels();
	assignTitleLabels();
	visibleTitleLables();
}
