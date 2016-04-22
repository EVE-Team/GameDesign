#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class CMainMenuScene : public Layer
{
public:
	static Scene* CreateScene();
	bool Init(Scene *scene);

	void MenuCloseCallback();
	void SetEventListener();
	void CreateSceneLabels();
	void CMainMenuScene::ChooseAction(int action);
	void CMainMenuScene::ShowStatistics();
	 
	CMainMenuScene();
	~CMainMenuScene();

	CREATE_FUNC(CMainMenuScene);
private:

};

