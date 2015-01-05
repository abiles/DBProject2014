#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"


class SearchLayer : public cocos2d::LayerColor, public cocos2d::ui::EditBoxDelegate
{
public:
	virtual bool init();

	void		 searchBackEvent(cocos2d::Ref* sender);
	void		 afterSearchBackEvent(cocos2d::Ref* sender);
	void	     initTitleLabels();
	void		 createTitleLabels();
	void		 assignTitleLabels();
	void		 visibleTitleLables();
	void		 unvisibleTitleLables();
	void		 editBoxInit();

	CREATE_FUNC(SearchLayer);
private:
	virtual void				  editBoxReturn(cocos2d::ui::EditBox* editBox);

	cocos2d::ui::EditBox*		  m_ContentsSearchEditBox = nullptr;
	cocos2d::Menu*				  m_BackSearchMenu = nullptr;
	cocos2d::Menu*				  m_BackAfterSearchMenu = nullptr;
	std::vector<cocos2d::Label*>  m_SearchInfoLabels;
	std::vector<cocos2d::Label*>  m_SearchInfoTitleLabels;


};