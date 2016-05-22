#include "Carriage.h"
#include "cocos2d.h"
#include "string"
#include "HelloWorldScene.h"

USING_NS_CC;

using namespace std;
using namespace cocos2d;

CCarriage::CCarriage(const string &fileName)
	: m_spriteFileName(fileName)
{
}

CCarriage::~CCarriage()
{
}

CCarriage* CCarriage::Create(const string &fileName)
{
	auto enemySprite = new (nothrow)CCarriage(fileName);
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

bool CCarriage::Init(Sprite *sprite)
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

void CCarriage::SetContactListener()
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

void CCarriage::TouchEvent(Touch* touch)
{
	//this->setVisible(false);
	auto newSprite = CCarriage::Create(m_spriteFileName);
	auto scene = dynamic_cast<HelloWorld*>(this->getParent());
	newSprite->setPosition(Vec2(400, 50));
	scene->addChild(newSprite, 1);
}