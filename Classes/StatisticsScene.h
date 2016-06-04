#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class CStatisticsScene : public Layer
{
public:
	static Scene* CreateScene();
	bool Init(Scene *scene);

	void SetEventListener();
	void CreateSceneLabels();

	CStatisticsScene();
	~CStatisticsScene();
	CREATE_FUNC(CStatisticsScene);
	std::vector<int> GetHighScore();
};

