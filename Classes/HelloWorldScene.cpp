#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "CSequenceOfMine.h"
#include "Point.h"
#include "AirPLane.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = CBackGround::Create(CONSTANTS::SEA_SPRITE_FILENAME);
	this->addChild(backGround, 0);

	auto sequence = new CSequenceOfMine();
	auto seq = sequence->Create(3);

	int i = 0;
	for (set<MyPoint*>::iterator it = seq.begin(); it != seq.end(), i < 3; ++it, ++i)
	{
		auto bomb = CBomb::Create(CONSTANTS::MINE_SPRITE_FILENAME);
		bombs.push_back(bomb);
		this->addChild(bomb, 0);

		auto elem = *it;
		bombs[i]->setPosition(Vec2(elem->x, elem->y));
	}

	auto airplane = CAirPLane::Create(CONSTANTS::AIRPLANE_SPRITE_FILENAME);
	this->addChild(airplane, 1);
	airplane->TestFly(seq);

	this->scheduleUpdate();
    return true;
}


void HelloWorld::update(float delta)
{
	for (size_t i = 0; i < bombs.size(); ++i)
	{
		if (bombs[i]->isVisible())
		{
			return;
		}
	}
	auto scene = CMainMenuScene::CreateScene();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
