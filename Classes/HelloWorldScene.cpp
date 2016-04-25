#include "HelloWorldScene.h"
#include "Bomb.h"
#include "BackGround.h"
#include "CONSTANTS.h"

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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
 //   auto closeItem = MenuItemImage::create(
 //                                          "CloseNormal.png",
 //                                          "CloseSelected.png",
 //                                          CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
 //   
	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
 //                               origin.y + closeItem->getContentSize().height/2));

 //   // create menu, it's an autorelease object
 //   auto menu = Menu::create(closeItem, NULL);
 //   menu->setPosition(Vec2::ZERO);
 //   this->addChild(menu, 1);

 //   /////////////////////////////
 //   // 3. add your codes below...

 //   // add a label shows "Hello World"
 //   // create and initialize a label
 //   
 //   auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
 //   
 //   // position the label on the center of the screen
 //   label->setPosition(Vec2(origin.x + visibleSize.width/2,
 //                           origin.y + visibleSize.height - label->getContentSize().height));

 //   // add the label as a child to this layer
 //   this->addChild(label, 1);

 //   // add "HelloWorld" splash screen"
 //   auto sprite = Sprite::create("HelloWorld.png");

 //   // position the sprite on the center of the screen
 //   sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

 //   // add the sprite as a child to this layer
 //   this->addChild(sprite, 0);

	auto backGround = CBackGround::Create(CONSTANTS::SEA_SPRITE_FILENAME);
	this->addChild(backGround, 0);

	int shift_x = 150;
	int shift_y = 100;


	std::vector<CBomb*> bombs;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			auto bomb = CBomb::Create("mine.png");
			bomb->setPosition(Vec2(origin.x + shift_x, origin.y + shift_y));

			//auto listener = EventListenerTouchOneByOne::create();
			//listener->setSwallowTouches(true);
			//listener->onTouchBegan = [](Touch* touch, Event* event){
			//	auto target = static_cast<Sprite*>(event->getCurrentTarget());
			//	target->setVisible(false);
			//	Rect rect = target->getBoundingBox();

			//	if (rect.containsPoint()
			//	{

			//	}
			//	return true;
			//	//	//Move the position of current button sprite
			//	//target->setPosition(target->getPosition() + touch->getDelta());
			//};
			///*auto contactListener = EventListenerTouch::create()*/;
			////listener1->onTouchBegan = CC_CALLBACK_1(CBomb::onContactBegin, this);
			//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, bomb);

			this->addChild(bomb, 0);
			shift_x += 50;
		}
		shift_y += 100;
		shift_x = 150;
	}
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
