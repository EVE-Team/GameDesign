#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "Sequence.h"
#include "Point.h"

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

	auto sequence = new MyCSequence();
	auto seq = sequence->Create(3);

	for (int i = 0; i < 3; ++i)
	{
		auto bomb = CBomb::Create(CONSTANTS::MINE_SPRITE_FILENAME);
		bombs.push_back(bomb);
		bombs[i]->setPosition(Vec2(seq[i]->x, seq[i]->y));
	}

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
