#pragma once

#include "cocos2d.h"
#include "Bomb.h"
#include "BackGround.h"
#include "Constants.h"
#include "Carriage.h"
#include "Point.h"


class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void update(float delta);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
	void FillBasicPoints();
	std::vector<CCarriage*> GetWagons();
	std::vector<CCarriage*> GetBasicWagons();
	void SetWagons(std::vector<CCarriage*> wagons);

	int shift = 0;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	std::vector<CCarriage*> m_toFill;
	std::vector<MyPoint*> m_basicPoints;
	std::vector<CCarriage*> m_wagons;
	cocos2d::MoveTo* carriageMove;
	bool tFlag = true;
	cocos2d::Layer* a;
};