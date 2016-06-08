#include "PauseButton.h"
#include "RailTransport.h"
#include <string>
#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "PauseScene.h"

using namespace std;
using namespace cocos2d;

CPauseButton::CPauseButton(const string &fileName)
	: m_spriteFileName(fileName)
{
}

CPauseButton* CPauseButton::Create(const string &fileName)
{
	auto sprite = new (nothrow)CPauseButton(fileName);
	if (sprite && sprite->initWithFile(fileName))
	{
		if (!sprite->Init(sprite))
		{
			CC_SAFE_DELETE(sprite);
			return nullptr;
		}
		else
		{
			sprite->autorelease();
			sprite->SetContactListener();
			return sprite;
		}
	}
	else
	{
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
}

bool CPauseButton::Init(Sprite *sprite)
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

void CPauseButton::SetContactListener()
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
		auto scene = CPauseScene::createScene();
		Director::getInstance()->replaceScene(scene);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void CPauseButton::RemoveListener()
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}