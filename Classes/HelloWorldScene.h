#pragma once

#include "cocos2d.h"
#include "Bomb.h"
#include "BackGround.h"
#include "Constants.h"
#include "Point.h"
#include "BackCarriage.h"

class CRailTransport;
class CCarriage;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	//void update(float delta);
    
	void InitBasicObjects();
	CRailTransport* m_railTransport;
	int GetLifes();
	void SetLifes(int lifes);	
	void BeginLevel();	
	void ShowState(const std::string& text);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void SetListenersForWagons();
	
private:
	std::vector<CCarriage*> m_wagons;
	int m_lifes = 3;
	int m_length;
};