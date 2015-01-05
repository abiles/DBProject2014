#include "pch.h"
#include "EditContentsLayer.h"
#include "util.h"
#include "DBManager.h"

USING_NS_CC;

bool EditContentsLayer::init()
{


	if (!LayerColor::initWithColor(Color4B::BLACK))
		return false;


	initAddBox();

	
	initDeleteBox();

	initAddMenu();
	initDeleteMenu();
	initBackMenu();

	return true;
}

void EditContentsLayer::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
	const char* tmpText = editBox->getText();
	int len = strlen(tmpText);

	if (editBox->getName() == "addId")
		MultiByteToWideChar(0, 0, tmpText, len + 1, m_AddId, len + 1);
	else if (editBox->getName() == "addWeek")
		MultiByteToWideChar(0, 0, tmpText, len + 1, m_AddWeek, len + 1);
	else if (editBox->getName() == "addIdx")
		MultiByteToWideChar(0, 0, tmpText, len + 1, m_AddIdx, len + 1);
	else if (editBox->getName() == "addSub")
	{
		MultiByteToWideChar(CP_UTF8, 0, tmpText, len + 1, m_AddSub, len + 1);
		char tmpMultiChar[100] = { 0, };
		WideCharToMultiByte(CP_ACP, 0, m_AddSub, -1, tmpMultiChar, 100, 0, 0);
		editBox->setText(tmpMultiChar);
	}
	else if (editBox->getName() == "deleteId")
		MultiByteToWideChar(0, 0, tmpText, len + 1, m_DeleteId, len + 1);
	else if (editBox->getName() == "deleteWeek")
		MultiByteToWideChar(0, 0, tmpText, len + 1, m_DeleteWeek, len + 1);
	else
		MultiByteToWideChar(0, 0, tmpText, len + 1, m_DeleteIdx, len + 1);



}

void EditContentsLayer::initAddBox()
{
	m_AddCourseId = ui::EditBox::create(Size(200, 70), "newEditBox.png");
	m_AddCourseId->setPosition(Point(WINSIZE_WIDTH / 8, WINSIZE_HEIGHT / 5 * 4));
	m_AddCourseId->setFont("noto sans korean bold", 20);
	m_AddCourseId->setFontColor(Color3B::BLACK);
	m_AddCourseId->setPlaceHolder("추가 내용 ID 입력");
	m_AddCourseId->setPlaceholderFontName("noto sans korean bold");
	m_AddCourseId->setPlaceholderFontColor(Color3B::BLACK);
	m_AddCourseId->setMaxLength(6);
	m_AddCourseId->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_AddCourseId->setDelegate(this);
	m_AddCourseId->setName("addId");
	this->addChild(m_AddCourseId, 1);

	m_AddCourseWeek = ui::EditBox::create(Size(200, 70), "newEditBox.png");
	m_AddCourseWeek->setPosition(Point(WINSIZE_WIDTH / 8, WINSIZE_HEIGHT / 5 * 3));
	m_AddCourseWeek->setFont("noto sans korean bold", 20);
	m_AddCourseWeek->setFontColor(Color3B::BLACK);
	m_AddCourseWeek->setPlaceHolder("추가 내용 Week 입력");
	m_AddCourseWeek->setPlaceholderFontName("noto sans korean bold");
	m_AddCourseWeek->setPlaceholderFontColor(Color3B::BLACK);
	m_AddCourseWeek->setMaxLength(6);
	m_AddCourseWeek->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_AddCourseWeek->setDelegate(this);
	m_AddCourseWeek->setName("addWeek");
	this->addChild(m_AddCourseWeek, 1);

	m_AddCourseIdx = ui::EditBox::create(Size(200, 70), "newEditBox.png");
	m_AddCourseIdx->setPosition(Point(WINSIZE_WIDTH / 8, WINSIZE_HEIGHT / 5 * 2));
	m_AddCourseIdx->setFont("noto sans korean bold", 20);
	m_AddCourseIdx->setFontColor(Color3B::BLACK);
	m_AddCourseIdx->setPlaceHolder("추가 내용 Idx 입력");
	m_AddCourseIdx->setPlaceholderFontName("noto sans korean bold");
	m_AddCourseIdx->setPlaceholderFontColor(Color3B::BLACK);
	m_AddCourseIdx->setMaxLength(6);
	m_AddCourseIdx->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_AddCourseIdx->setDelegate(this);
	m_AddCourseIdx->setName("addIdx");
	this->addChild(m_AddCourseIdx, 1);

	m_AddCourseSubstance = ui::EditBox::create(Size(200, 70), "newEditBox.png");
	m_AddCourseSubstance->setPosition(Point(WINSIZE_WIDTH / 8, WINSIZE_HEIGHT / 5));
	m_AddCourseSubstance->setFont("noto sans korean bold", 20);
	m_AddCourseSubstance->setFontColor(Color3B::BLACK);
	m_AddCourseSubstance->setPlaceHolder("추가 내용 입력");
	m_AddCourseSubstance->setPlaceholderFontName("noto sans korean bold");
	m_AddCourseSubstance->setPlaceholderFontColor(Color3B::BLACK);
	m_AddCourseSubstance->setMaxLength(6);
	m_AddCourseSubstance->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_AddCourseSubstance->setDelegate(this);
	m_AddCourseSubstance->setName("addSub");
	this->addChild(m_AddCourseSubstance, 1);
}

void EditContentsLayer::initDeleteBox()
{
	m_DeleteCourseId = ui::EditBox::create(Size(200, 70), "deleteBox.png");
	m_DeleteCourseId->setPosition(Point(WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 5 * 4));
	m_DeleteCourseId->setFont("noto sans korean bold", 20);
	m_DeleteCourseId->setFontColor(Color3B::BLACK);
	m_DeleteCourseId->setPlaceHolder("삭제 ID 입력");
	m_DeleteCourseId->setPlaceholderFontName("noto sans korean bold");
	m_DeleteCourseId->setPlaceholderFontColor(Color3B::BLACK);
	m_DeleteCourseId->setMaxLength(6);
	m_DeleteCourseId->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_DeleteCourseId->setDelegate(this);
	m_DeleteCourseId->setName("deleteId");
	this->addChild(m_DeleteCourseId, 1);

	m_DeleteCourseWeek = ui::EditBox::create(Size(200, 70), "deleteBox.png");
	m_DeleteCourseWeek->setPosition(Point(WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 5 * 3));
	m_DeleteCourseWeek->setFont("noto sans korean bold", 20);
	m_DeleteCourseWeek->setFontColor(Color3B::BLACK);
	m_DeleteCourseWeek->setPlaceHolder("삭제 Week 입력");
	m_DeleteCourseWeek->setPlaceholderFontName("noto sans korean bold");
	m_DeleteCourseWeek->setPlaceholderFontColor(Color3B::BLACK);
	m_DeleteCourseWeek->setMaxLength(6);
	m_DeleteCourseWeek->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_DeleteCourseWeek->setDelegate(this);
	m_DeleteCourseWeek->setName("deleteWeek");
	this->addChild(m_DeleteCourseWeek, 1);

	m_DeleteCourseIdx = ui::EditBox::create(Size(200, 70), "deleteBox.png");
	m_DeleteCourseIdx->setPosition(Point(WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 5 * 2));
	m_DeleteCourseIdx->setFont("noto sans korean bold", 20);
	m_DeleteCourseIdx->setFontColor(Color3B::BLACK);
	m_DeleteCourseIdx->setPlaceHolder("삭제 IDX 입력");
	m_DeleteCourseIdx->setPlaceholderFontName("noto sans korean bold");
	m_DeleteCourseIdx->setPlaceholderFontColor(Color3B::BLACK);
	m_DeleteCourseIdx->setMaxLength(6);
	m_DeleteCourseIdx->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	m_DeleteCourseIdx->setDelegate(this);
	m_DeleteCourseIdx->setName("deleteIdx");
	this->addChild(m_DeleteCourseIdx, 1);
}

void EditContentsLayer::backMenuEvent(cocos2d::Ref* psender)
{
	setVisible(false);
}

void EditContentsLayer::initAddMenu()
{
	auto addMenu = MenuItemImage::create("addMenu.png", "addMenuPress.png",
										  CC_CALLBACK_1(EditContentsLayer::addMenuEvent, this));

	addMenu->setScale(0.7f);
	addMenu->setPosition(Point(WINSIZE_WIDTH - addMenu->getContentSize().width / 2, WINSIZE_HEIGHT / 8 + 300));

	m_AddMenu = Menu::create(addMenu, NULL);
	m_AddMenu->setPosition(Point::ZERO);
	this->addChild(m_AddMenu, 1);
}

void EditContentsLayer::initDeleteMenu()
{
	auto deleteMenu = MenuItemImage::create("deleteMenu.png", "deleteMenuPress.png",
											CC_CALLBACK_1(EditContentsLayer::deleteMenuEvent, this));

	deleteMenu->setScale(0.7f);
	deleteMenu->setPosition(Point(WINSIZE_WIDTH - deleteMenu->getContentSize().width / 2, WINSIZE_HEIGHT / 8 + 150));

	m_DeleteMenu = Menu::create(deleteMenu, NULL);
	m_DeleteMenu->setPosition(Point::ZERO);
	this->addChild(m_DeleteMenu, 1);
}

void EditContentsLayer::initBackMenu()
{
	auto backMenu = MenuItemImage::create("back.png", "back.png",
										  CC_CALLBACK_1(EditContentsLayer::backMenuEvent, this));

	backMenu->setScale(0.7f);
	backMenu->setPosition(Point(WINSIZE_WIDTH - backMenu->getContentSize().width / 2, WINSIZE_HEIGHT / 8));

	m_BackMenu = Menu::create(backMenu, NULL);
	m_BackMenu->setPosition(Point::ZERO);
	this->addChild(m_BackMenu, 1);
}

void EditContentsLayer::addMenuEvent(cocos2d::Ref* psender)
{
	GET_DBMANAGER()->addContents(m_AddId, m_AddWeek, m_AddIdx, m_AddSub);
}

void EditContentsLayer::deleteMenuEvent(cocos2d::Ref* psender)
{
	GET_DBMANAGER()->deleteContents(m_DeleteId, m_DeleteWeek, m_DeleteIdx);
}
