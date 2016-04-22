#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class CMainMenuScene : public Layer
{
public:
	static Scene* CreateScene();
	bool Init(Scene *scene);

	void MenuCloseCallback(Ref* pSender);
	void SetEventListener();
	void CreateSceneLabels();
	void ChooseAction(int action);
	void ShowStatistics();
	 
	CMainMenuScene();
	~CMainMenuScene();

	CREATE_FUNC(CMainMenuScene);
private:

};

