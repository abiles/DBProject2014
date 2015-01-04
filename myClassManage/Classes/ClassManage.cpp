#include "pch.h"
#include "ClassManage.h"
#include "DBManager.h"


USING_NS_CC;

Scene* ClassManage::createScene()
{

    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ClassManage::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ClassManage::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	DBManager* m_DBManager = new DBManager();
	if (!m_DBManager->connectToDB())
		return false;
    
    m_VisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("ClassManageMent", "fonts/Marker Felt.ttf", 40);

	label->setPosition(Vec2(origin.x + m_VisibleSize.width / 2,
		origin.y + m_VisibleSize.height - label->getContentSize().height));

	this->addChild(label, 1);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(ClassManage::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + m_VisibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	m_EditBox = ui::EditBox::create(Size(300, 100), "SpriteToolEditBox.png");
	editBoxInit();
	this->addChild(m_EditBox, 1);

	/*auto nameInput = LabelTTF::create("inputID", "Calibri", 24);
	Point nameInputPos = Point(200, 200);
	nameInput->setPosition(nameInputPos);
	this->addChild(nameInput, 1);
	*/
 
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

ClassManage::~ClassManage()
{
	if (m_DBManager)
	{
		delete m_DBManager;
	}
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

	m_UserId = editBox->getText();
	if (m_DBManager->iSInputIDExist(m_UserId))
	{
		return;
	}
	else
	{
		return;
	}
}

void ClassManage::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	if (!editBox)
		return;
}

void ClassManage::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	if (!editBox)
		return;
}

void ClassManage::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	if (!editBox)
		return;
}


















