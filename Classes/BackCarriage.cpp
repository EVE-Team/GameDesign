#include "BackCarriage.h"
#include "cocos2d.h"
#include "string"
#include "HelloWorldScene.h"

USING_NS_CC;

using namespace std;
using namespace cocos2d;

BackCarriage::BackCarriage(const string &fileName)
	: m_spriteFileName(fileName)
{
}


BackCarriage::~BackCarriage()
{
}

BackCarriage* BackCarriage::Create(const string &fileName)
{
	auto carriageSprite = new (nothrow)BackCarriage(fileName);
	if (carriageSprite && carriageSprite->initWithFile(fileName))
	{
		if (!carriageSprite->Init(carriageSprite))
		{
			CC_SAFE_DELETE(carriageSprite);
			return nullptr;
		}
		else
		{
			carriageSprite->autorelease();
			return carriageSprite;
		}
	}
	else
	{
		CC_SAFE_DELETE(carriageSprite);
		return nullptr;
	}
}

bool BackCarriage::Init(Sprite *sprite)
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

void BackCarriage::SetContactListener()
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

void BackCarriage::TouchEvent(Touch* touch)
{
	auto scene = dynamic_cast<HelloWorld*>(this->getParent());
	scene->shift -= this->getContentSize().width;
	int shift = (scene->shift);

	vector<BackCarriage*> wag = scene->GetWagons();
	if (wag.size())
	{
		auto car = wag.back();
		wag.pop_back();
		scene->SetWagons(wag);
		scene->removeChildByTag(car->getTag(), true);
	}
}