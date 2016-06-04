#pragma once

#include "cocos2d.h"
#include "BackGround.h"
#include "Constants.h"
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
	void BeginLevel();	
	void ShowState(const std::string& text);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void SetListenersForWagons();
	void SaveScore(const std::string&);
private:
	std::vector<CCarriage*> m_wagons;
	int m_length;
};