#include "Bomb.h"
#include "cocos2d.h"
#include "string"

USING_NS_CC;

using namespace std;
using namespace cocos2d;

CBomb::CBomb()
{
}

CBomb::~CBomb()
{
}

CBomb* CBomb::Create(const string &fileName)
{
	auto enemySprite = new (nothrow)CBomb();
	if (enemySprite && enemySprite->initWithFile(fileName))
	{
		if (!enemySprite->Init(enemySprite))
		{
			CC_SAFE_DELETE(enemySprite);
			return nullptr;
		}
		else
		{
			enemySprite->autorelease();
			return enemySprite;
		}
	}
	else
	{
		CC_SAFE_DELETE(enemySprite);
		return nullptr;
	}
}

bool CBomb::Init(Sprite *sprite)
{
	if (sprite)
	{
		SetContactListener();

		return true;
	}
	else
	{
		return false;
	}
}


void CBomb::SetContactListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [&](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point location = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0,0,s.width,s.height);

		if (rect.containsPoint(location))
		{
			return true;
		}
		
		return false;
	//	//Move the position of current button sprite
		//target->setPosition(target->getPosition() + touch->getDelta());
	};
	listener1->onTouchEnded = [=](Touch* touch, Event* event){
		TouchEvent(touch);
	};
	///*auto contactListener = EventListenerTouch::create()*/;
	////listener1->onTouchBegan = CC_CALLBACK_1(CBomb::onContactBegin, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
}

void CBomb::TouchEvent(Touch* touch)
{

	this->setVisible(false);
}