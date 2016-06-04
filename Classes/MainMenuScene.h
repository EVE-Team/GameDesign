#pragma once
#include "cocos2d.h"

class CMainMenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool init();
	void CreateSceneLabels();	 
	CREATE_FUNC(CMainMenuScene);
};

