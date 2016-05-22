#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "CSequenceOfMine.h"
#include "Point.h"
#include "Carriage.h"

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

	auto carriage1 = CCarriage::Create(CONSTANTS::CARRIAGE1_SPRITE_FILENAME);
	carriage1->setPosition(Vec2(60, 280));
	this->addChild(carriage1, 1);

	auto carriage2 = CCarriage::Create(CONSTANTS::CARRIAGE2_SPRITE_FILENAME);
	carriage2->setPosition(Vec2(180, 280));
	this->addChild(carriage2, 1);

	auto carriage3 = CCarriage::Create(CONSTANTS::CARRIAGE3_SPRITE_FILENAME);
	carriage3->setPosition(Vec2(300, 280));
	this->addChild(carriage3, 1);

	auto carriage4 = CCarriage::Create(CONSTANTS::CARRIAGE4_SPRITE_FILENAME);
	carriage4->setPosition(Vec2(420, 280));
	this->addChild(carriage4, 1);

	auto carriage5 = CCarriage::Create(CONSTANTS::CARRIAGE5_SPRITE_FILENAME);
	carriage5->setPosition(Vec2(60, 200));
	this->addChild(carriage5, 1);

	auto carriage6 = CCarriage::Create(CONSTANTS::CARRIAGE6_SPRITE_FILENAME);
	carriage6->setPosition(Vec2(180, 200));
	this->addChild(carriage6, 1);

	auto carriage7 = CCarriage::Create(CONSTANTS::CARRIAGE7_SPRITE_FILENAME);
	carriage7->setPosition(Vec2(300, 200));
	this->addChild(carriage7, 1);

	auto carriage8 = CCarriage::Create(CONSTANTS::CARRIAGE8_SPRITE_FILENAME);
	carriage8->setPosition(Vec2(420, 200));
	this->addChild(carriage8, 1);

	/*auto sequence = new CSequenceOfMine();
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
    */
	return true;
}


void HelloWorld::update(float delta)
{
	/*for (size_t i = 0; i < bombs.size(); ++i)
	{
		if (bombs[i]->isVisible())
		{
			return;
		}
	}
	auto scene = CMainMenuScene::CreateScene();
	Director::getInstance()->replaceScene(scene);*/
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
