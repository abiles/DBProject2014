#include "pch.h"
#include "EditMyCourseLayer.h"
#include "util.h"
#include "DBManager.h"

USING_NS_CC;

bool EditMyCourseLayer::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
		return false;

	m_AddCourse = ui::EditBox::create(Size(300, 100), "newEditBox.png");
	addBoxInit();
	this->addChild(m_AddCourse, 2);
	
	m_DeleteCourse = ui::EditBox::create(Size(300, 100), "deleteBox.png");
	deleteBoxInit();
	this->addChild(m_DeleteCourse, 2);

	auto backMenu = MenuItemImage::create("back.png", "back.png",
										  CC_CALLBACK_1(EditMyCourseLayer::backMenuEvent, this));

	backMenu->setScale(0.7f);
	backMenu->setPosition(Point(WINSIZE_WIDTH - backMenu->getContentSize().width / 2, WINSIZE_HEIGHT / 8));

	m_BackMenu = Menu::create(backMenu, NULL);
	m_BackMenu->setPosition(Point::ZERO);
	this->addChild(m_BackMenu, 1);

	return true;
}

void EditMyCourseLayer::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
	SQLWCHAR editContens[100] = { 0, };
	const char* tmpText = editBox->getText();
	int len = strlen(tmpText);
	MultiByteToWideChar(0, 0, tmpText, len + 1, editContens, len + 1);
	if (editBox->getName() == "add")
	{	
		GET_DBMANAGER()->updateMyCourse(editContens);
	}
	else
	{
		GET_DBMANAGER()->deleteMyCourse(editContens);

	}
}

void EditMyCourseLayer::addBoxInit()
{
	m_AddCourse->setPosition(Point(WINSIZE_WIDTH/ 2, WINSIZE_HEIGHT / 3 * 2));
	m_AddCourse->setFont("noto sans korean bold", 35);
	m_AddCourse->setFontColor(Color3B::BLACK);
	m_AddCourse->setPlaceHolder("추가 과목 ID 입력");
	m_AddCourse->setPlaceholderFontName("noto sans korean bold");
	m_AddCourse->setPlaceholderFontColor(Color3B::BLACK);
	m_AddCourse->setMaxLength(6);
	m_AddCourse->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_AddCourse->setDelegate(this);
	m_AddCourse->setName("add");
}

void EditMyCourseLayer::deleteBoxInit()
{
	m_DeleteCourse->setPosition(Point(WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 3));
	m_DeleteCourse->setFont("noto sans korean bold", 35);
	m_DeleteCourse->setFontColor(Color3B::BLACK);
	m_DeleteCourse->setPlaceHolder("삭제 과목 ID 입력");
	m_DeleteCourse->setPlaceholderFontName("noto sans korean bold");
	m_DeleteCourse->setPlaceholderFontColor(Color3B::BLACK);
	m_DeleteCourse->setMaxLength(6);
	m_DeleteCourse->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_DeleteCourse->setDelegate(this);
	m_DeleteCourse->setName("delete");
}

void EditMyCourseLayer::backMenuEvent(cocos2d::Ref* psender)
{
	setVisible(false);
}
