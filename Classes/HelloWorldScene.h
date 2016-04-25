#pragma once

#include "cocos2d.h"
#include "Bomb.h"
#include "BackGround.h"
#include "CONSTANTS.h"


class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void update(float delta);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	std::vector<CBomb*> bombs;
};