#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

class DBManager;
class ClassManage : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
public:
	~ClassManage();
    
    static cocos2d::Scene* createScene();

    virtual bool init();
    void		 menuCloseCallback(cocos2d::Ref* pSender);
	
    
	void		 editBoxInit();
   
    CREATE_FUNC(ClassManage);

private:
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);


	const char*			  m_UserId = nullptr;
	DBManager*			  m_DBManager = nullptr;
	cocos2d::Size		  m_VisibleSize = cocos2d::Size::ZERO;
	cocos2d::ui::EditBox* m_EditBox = nullptr;

};

#endif // __HELLOWORLD_SCENE_H__
