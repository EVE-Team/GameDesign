#include "HelloWorldScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
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


	//std::vector<CBomb*> bombs;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			auto bomb = CBomb::Create("mine.png");
			bomb->setPosition(Vec2(origin.x + shift_x, origin.y + shift_y));
			this->addChild(bomb, 0);
			bombs.push_back(bomb);
			shift_x += 50;
		}
		shift_y += 100;
		shift_x = 150;
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
