#pragma once
#include "cocos2d.h"

class CStatisticsScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void SetEventListener();
	void CreateSceneLabels();
	CREATE_FUNC(CStatisticsScene);
	std::vector<int> GetHighScore();
};

