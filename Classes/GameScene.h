#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class CGameScene : public Layer
{
public:
	static Scene* CreateScene();
	bool Init(Scene *scene);

	void SetEventListener();
	void CreateSceneLabels();

	CGameScene();
	~CGameScene();
	CREATE_FUNC(CGameScene);
private:

};

