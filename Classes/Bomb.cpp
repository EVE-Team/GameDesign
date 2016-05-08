#include "Bomb.h"
#include "cocos2d.h"
#include "string"

USING_NS_CC;

using namespace std;
using namespace cocos2d;

CBomb::CBomb()
	: position_x(0)
	, position_y(0)
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
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point location = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0,0,s.width,s.height);

		if (rect.containsPoint(location))
		{
			return true;
		}
		
		return false;
	};
	listener->onTouchEnded = [=](Touch* touch, Event* event){
		TouchEvent(touch);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void CBomb::TouchEvent(Touch* touch)
{
	this->setVisible(false);
}

void CBomb::SetPosition(int x, int y)
{
	position_x = x;
	position_y = y;
}