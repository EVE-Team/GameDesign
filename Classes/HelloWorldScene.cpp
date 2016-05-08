#include "HelloWorldScene.h"
#include "MainMenuScene.h"

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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = CBackGround::Create(CONSTANTS::SEA_SPRITE_FILENAME);
	this->addChild(backGround, 0);

	int shift_x = 150;
	int shift_y = 100;

	std::vector<int> position_X;
	std::vector<int> position_Y;

	position_X.push_back(60);
	position_Y.push_back(160);

	position_X.push_back(120);
	position_Y.push_back(60);

	position_X.push_back(120);
	position_Y.push_back(260);

	position_X.push_back(180);
	position_Y.push_back(160);

	position_X.push_back(240);
	position_Y.push_back(60);

	position_X.push_back(240);
	position_Y.push_back(260);

	position_X.push_back(300);
	position_Y.push_back(160);

	position_X.push_back(360);
	position_Y.push_back(60);

	position_X.push_back(360);
	position_Y.push_back(260);

	position_X.push_back(420);
	position_Y.push_back(160);

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			auto bomb = CBomb::Create(CONSTANTS::MINE_SPRITE_FILENAME);
			//bomb->setPosition(Vec2(origin.x + shift_x, origin.y + shift_y));
			this->addChild(bomb, 0);
			bombs.push_back(bomb);
			shift_x += 50;
		}
		shift_y += 100;
		shift_x = 150;
	}

	for (int i = 0; i < 10; ++i)
	{
		bombs[i]->setPosition(Vec2(position_X[i], position_Y[i]));
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
