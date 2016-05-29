#pragma once

#include "cocos2d.h"
#include "Bomb.h"
#include "BackGround.h"
#include "Constants.h"
#include "Carriage.h"
#include "Point.h"
#include "BackCarriage.h"


class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void update(float delta);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
	void FillBasicPoints();
	std::vector<BackCarriage*> GetWagons();
	std::vector<Sprite*> GetBasicWagons();
	void SetWagons(std::vector<BackCarriage*> wagons);

	void Update(float dt);

	int GetLifes();
	void SetLifes(int lifes);

	int shift = 0;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	void CreateRailTransport();
	std::vector<BackCarriage*> m_toFill;
	std::vector<MyPoint*> m_basicPoints;
	std::vector<Sprite*> m_wagons;
	cocos2d::MoveTo* carriageMove;
	bool IsTrainRunning = false;
	int trainRunningEndPos = 0;
	cocos2d::Layer* a;
	int m_lifes = 3;
};