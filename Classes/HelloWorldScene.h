#pragma once
#include "cocos2d.h"

class CRailTransport;
class CCarriage;
class CPauseButton;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
	void InitBasicObjects();
	CRailTransport* m_railTransport;
	void BeginLevel();	
	void ShowState(const bool right);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void SetListenersForWagons();
	void SaveScore(const std::string&);
	void RemoveListenersForWagons();
	void onExit();
	void SaveResult();
private:
	std::vector<CCarriage*> m_wagons;
	int m_length;
	cocos2d::Label* m_scoreLabel;
	cocos2d::Sprite* m_lifesSprite;
	cocos2d::Label* m_lifesLabel;
	CPauseButton* m_btnPause;
};