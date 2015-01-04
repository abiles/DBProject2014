#include "pch.h"
#include "ClassManage.h"
#include "DBManager.h"
#include "util.h"


USING_NS_CC;

Scene* ClassManage::createScene()
{
	auto scene = Scene::create();
	auto layer = ClassManage::create();
	scene->addChild(layer);
	return scene;
}

bool ClassManage::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	//DB 연결
	if (!GET_DBMANAGER()->connectToDB())
		return false;
	wmemset(m_UserId, 0, sizeof(m_UserId));
	
	//크기 구해놓기
	m_VisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initLabels();

	//ID 받는 부분
	m_EditBox = ui::EditBox::create(Size(300, 100), "SpriteToolEditBox.png");
	editBoxInit();
	this->addChild(m_EditBox, FISRT_LAYER);

	return true;
}


void ClassManage::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void ClassManage::editBoxInit()
{
	m_EditBox->setPosition(Point(m_VisibleSize.width/ 2, m_VisibleSize.height / 2));
	m_EditBox->setFont("Calbri", 24);
	m_EditBox->setFontColor(Color3B::YELLOW);
	m_EditBox->setPlaceHolder("Input Your ID");
	m_EditBox->setPlaceholderFontName("Calbri");
	m_EditBox->setPlaceholderFontColor(Color3B::YELLOW);
	m_EditBox->setMaxLength(6);
	m_EditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_EditBox->setDelegate(this);
	
}

void ClassManage::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
	if (!editBox)
		return;

	const char* tmpText = editBox->getText();
	int len = strlen(tmpText);
	MultiByteToWideChar(0,0, tmpText, len + 1, m_UserId, len + 1);

	if (GET_DBMANAGER()->isInputIDExist(m_UserId))
	{
		m_FirstToSecondMenu->setVisible(true);
		return;
	}
	else
	{
		//존재하지 않는 ID일 때
		m_FirstToSecondMenu->setVisible(false);
		m_ResisterInfoLabel->setVisible(true);
		m_ResistrationMenu->setVisible(true);
		return;
	}
}

void ClassManage::resisterMenuEvent(cocos2d::Ref* pSender)
{
	m_ResisterResultLabel->setVisible(true);
	m_ResisterInfoLabel->setVisible(false);
	//userid를 등록하면 된다. 
	if (GET_DBMANAGER()->resisterNewUserId(m_UserId))
	{
		m_ResisterResultLabel->setString("resister Success!");
		m_ResistrationMenu->setVisible(false);
		m_FirstToSecondMenu->setVisible(true);
	}
	else
	{
		m_ResisterResultLabel->setString("resister Fail!");
		m_FirstToSecondMenu->setVisible(false);


	}
	//등록되었다면 다음 화면으로 넘어가기 
}

void ClassManage::initLabels()
{
	//종료 버튼
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(ClassManage::menuCloseCallback, this));

	closeItem->setPosition(Vec2( m_VisibleSize.width - closeItem->getContentSize().width / 2,
		closeItem->getContentSize().height / 2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, FISRT_LAYER);

	//제목 라벨
	auto label = Label::createWithTTF("ClassManageMent", "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2(m_VisibleSize.width / 2,
		m_VisibleSize.height - label->getContentSize().height));
	this->addChild(label, FISRT_LAYER);

	//등록해야되는지 알려주는 라벨
	m_ResisterInfoLabel = Label::createWithSystemFont("ID does not exist, resistration First", "Calbri", 20);
	m_ResisterInfoLabel->setPosition(Point(m_VisibleSize.width / 2, 220));
	this->addChild(m_ResisterInfoLabel, FISRT_LAYER);
	m_ResisterInfoLabel->setVisible(false);

	//등록결과 라벨
	m_ResisterResultLabel = Label::create();
	m_ResisterResultLabel->setSystemFontSize(20);
	m_ResisterResultLabel->setPosition(Point(m_VisibleSize.width / 2, 220));
	this->addChild(m_ResisterResultLabel, FISRT_LAYER);
	m_ResisterResultLabel->setVisible(false);

	//등록 메뉴
	auto resisterMenu = MenuItemImage::create("resisterButton.png",
											  "resisterButtonPress.png",
											  CC_CALLBACK_1(ClassManage::resisterMenuEvent, this));
	resisterMenu->setPosition(Point(m_VisibleSize.width / 2, 130));
	m_ResistrationMenu = Menu::create(resisterMenu, NULL);
	m_ResistrationMenu->setPosition(Point::ZERO);
	this->addChild(m_ResistrationMenu, FISRT_LAYER);
	m_ResistrationMenu->setVisible(false);

	//1장에서 2장으로 넘어가는 메뉴
	auto firstToSecondMenu = MenuItemImage::create("next.png", "nextPress.png",
												   CC_CALLBACK_1(ClassManage::firstToSecondMenuEvent, this));
	firstToSecondMenu->setPosition(Point(m_VisibleSize.width / 2, 130));
	m_FirstToSecondMenu = Menu::create(firstToSecondMenu, NULL);
	m_FirstToSecondMenu->setPosition(Point::ZERO);
	this->addChild(m_FirstToSecondMenu, FISRT_LAYER);
	m_FirstToSecondMenu->setVisible(false);
}

void ClassManage::firstToSecondMenuEvent(cocos2d::Ref* pSender)
{
	//다음 레이어를 소환하는 메뉴!
}
