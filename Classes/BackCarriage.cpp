#include "BackCarriage.h"
#include "RailTransport.h"

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
	auto parent = dynamic_cast<CRailTransport*>(this->getParent());
	auto remWag = parent->m_wagons.back();
	parent->m_wagons.pop_back();
	parent->m_userCreatedTrain.pop_back();
	float shift = parent->m_shift - remWag->getContentSize().width;
	parent->m_shift = shift;
	parent->removeChild(remWag, false);
}