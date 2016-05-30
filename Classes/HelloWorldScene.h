#pragma once

#include "cocos2d.h"
#include "Bomb.h"
#include "BackGround.h"
#include "Constants.h"
#include "Carriage.h"
#include "Point.h"
#include "BackCarriage.h"

class CRailTransport;

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
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	int m_lifes = 3;
	int m_length;
};