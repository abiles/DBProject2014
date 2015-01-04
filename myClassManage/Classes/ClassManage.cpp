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

	auto inputEditBox = ui::EditBox::create(Size(300, 100), "SpriteToolEditBox.png");
	editBoxInit(inputEditBox);
	this->addChild(inputEditBox, 1);

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

void ClassManage::editBoxInit(ui::EditBox* inputEditBox)
{
	inputEditBox->setPosition(Point(m_VisibleSize.width/ 2, m_VisibleSize.height / 2));
	inputEditBox->setFont("Calbri", 24);
	inputEditBox->setFontColor(Color3B::YELLOW);
	inputEditBox->setPlaceHolder("Input Your ID");
	inputEditBox->setPlaceholderFontName("Calbri");
	inputEditBox->setPlaceholderFontColor(Color3B::YELLOW);
	inputEditBox->setMaxLength(6);
	inputEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
}

void ClassManage::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
	if (!editBox)
		return;
	
	m_UserId = editBox->getText();
}
