#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

class DBManager;
class ClassManage : public cocos2d::Layer
{
public:
	~ClassManage();
    
    static cocos2d::Scene* createScene();

    virtual bool init();
    void		 menuCloseCallback(cocos2d::Ref* pSender);
	
    
	void		 editBoxInit(cocos2d::ui::EditBox* inputEditBox);
   
    CREATE_FUNC(ClassManage);

private:
	////에디트 박스 클릭하면 호출하는 메소드
	//virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);

	//에디트 박스 입력을 리턴키를 입력해서 종료할 때 출력되는 메소드
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);

	//에디트 박스를 클릭한 후 글자를 입력할 때마다 호출되는 메소드
	/*virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);*/

	//리턴키를 입력할 때 출력되는 메소드, 일반적으로 리턴키를 입력하면 editBoxEditingDidEnd()가 호출되고
	//editBoxReturn() 메소드가 그 다음으로 호출됩니다.
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);


	const char*			   m_UserId = nullptr;
	DBManager*		   m_DBManager = nullptr;
	cocos2d::Size	   m_VisibleSize = cocos2d::Size::ZERO;

};

#endif // __HELLOWORLD_SCENE_H__
