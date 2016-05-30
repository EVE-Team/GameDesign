#include "Train.h"
#include "cocos2d.h"
#include "string"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"


USING_NS_CC;

using namespace std;
using namespace cocos2d;

CTrain::CTrain()
{
}

CTrain::~CTrain()
{
}

CTrain* CTrain::Create(const string &fileName)
{
	auto enemySprite = new (nothrow)CTrain();
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

bool CTrain::Init(Sprite *sprite)
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

void CTrain::SetContactListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point location = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

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

void CTrain::TouchEvent(Touch* touch)
{
	auto parent = dynamic_cast<CRailTransport*>(this->getParent());
	parent->CheckGameState();
}
