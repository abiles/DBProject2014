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
	////����Ʈ �ڽ� Ŭ���ϸ� ȣ���ϴ� �޼ҵ�
	//virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);

	//����Ʈ �ڽ� �Է��� ����Ű�� �Է��ؼ� ������ �� ��µǴ� �޼ҵ�
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);

	//����Ʈ �ڽ��� Ŭ���� �� ���ڸ� �Է��� ������ ȣ��Ǵ� �޼ҵ�
	/*virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);*/

	//����Ű�� �Է��� �� ��µǴ� �޼ҵ�, �Ϲ������� ����Ű�� �Է��ϸ� editBoxEditingDidEnd()�� ȣ��ǰ�
	//editBoxReturn() �޼ҵ尡 �� �������� ȣ��˴ϴ�.
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);


	const char*			   m_UserId = nullptr;
	DBManager*		   m_DBManager = nullptr;
	cocos2d::Size	   m_VisibleSize = cocos2d::Size::ZERO;

};

#endif // __HELLOWORLD_SCENE_H__
