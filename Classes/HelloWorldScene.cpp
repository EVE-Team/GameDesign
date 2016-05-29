#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "SequenceOfCarriage.h"
#include "Point.h"
#include "Carriage.h"
#include "Train.h"
#include <json11.hpp>
#include "ui\CocosGUI.h"
#include "..\cocos2d\external\flatbuffers\util.h"
#include "proj.win32\RailTransport.h"

USING_NS_CC;

using namespace json11;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
	m_lifes = 3;
	FillBasicPoints();

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = CBackGround::Create(CONSTANTS::SEA_SPRITE_FILENAME);
	this->addChild(backGround, 0);

	Size carriageSize;

	for (size_t i = 1; i < 9; ++i)
	{
		auto carriage = CCarriage::Create(CONSTANTS::CARRIAGE_SPRITE_FILENAME + to_string(i) + CONSTANTS::CARRIAGE_FILENAME_RESOLUTION);
		carriage->setPosition(Vec2(m_basicPoints[i-1]->x, m_basicPoints[i-1]->y));
		carriage->setTag(i);
		carriageSize = carriage->getContentSize();
		this->addChild(carriage, 1);
	}

	auto train = CTrain::Create(CONSTANTS::TRAIN_SPRITE_FILENAME);
	train->setAnchorPoint(Vec2(0, 0));
	Size trainSize = train->getContentSize();
	train->setPosition(Vec2(0 - trainSize.width, 0));

	

	auto move = MoveTo::create(8.0, Vec2(600, 50));

	auto seq = &CSequenceOfCarriage::CSequenceOfCarriage();
	auto vec = seq->Create(3);

	int shift = 10;
	int startPosition = 0 - trainSize.width - shift;

	carriageMove = MoveTo::create(8.0, Vec2(1200, 50));
	
	a = CRailTransport::create();
	a->setPosition(Vec2(0, 45));
	this->addChild(a, 20);
	a->addChild(train, 1);

	for (size_t i = 0; i < vec.size(); ++i)
	{
		startPosition -= (carriageSize.width - 10);
		auto newCarriage = CCarriage::Create(CONSTANTS::CARRIAGE_SPRITE_FILENAME + to_string(vec[i]) + CONSTANTS::CARRIAGE_FILENAME_RESOLUTION);
		newCarriage->setAnchorPoint(Vec2(0, 0));
		newCarriage->setPosition(Vec2(startPosition, 0));
		newCarriage->setTag(vec[i]);
		startPosition -= shift;
		
		a->addChild(newCarriage, 1);
		//this->addChild(newCarriage, 1);
		m_wagons.push_back(newCarriage);
	}
	a->runAction(carriageMove);
	this->scheduleUpdate();
	

	//this->schedule(schedule_selector(HelloWorld::Update));

	return true;
}

void HelloWorld::FillBasicPoints()
{
	auto fileUtils = FileUtils::getInstance();
	string data = fileUtils->getStringFromFile(CONSTANTS::BASIC_POINTS::FILENAME);
	string err;
	auto  points = Json::parse(data, err);
	auto basicPoints = points[CONSTANTS::BASIC_POINTS::NAME].array_items();
	for (auto const& it : basicPoints)
	{
		auto point = new MyPoint();
		point->x = it[CONSTANTS::BASIC_POINTS::X].int_value();
		point->y = it[CONSTANTS::BASIC_POINTS::Y].int_value();
		m_basicPoints.push_back(point);
	}
}

vector<BackCarriage*> HelloWorld::GetWagons()
{
	return m_toFill;
}

vector<CCarriage*> HelloWorld::GetBasicWagons()
{
	return m_wagons;
}

void HelloWorld::SetWagons(vector<BackCarriage*> wagons)
{
	this->m_toFill = wagons;
}

int HelloWorld::GetLifes()
{
	return m_lifes;
}

void HelloWorld::SetLifes(int lifes)
{
	if (m_lifes < 3)
	{
		m_lifes += lifes;
	}
}

void HelloWorld::Update(float dt)
{
	while (m_lifes)
	{

	}
}

void HelloWorld::update(float delta)
{
	if ((a->getPositionX() > 1000) && (this->tFlag))
	{
		auto popLast = ui::Button::create();
		popLast->setTitleText("Pop last");
		popLast->setColor(Color3B::YELLOW);
		popLast->setTitleFontSize(30);
		popLast->setTitleFontName(CONSTANTS::FONT_NAME);
		popLast->setPosition(Vec2(50, 50));
		popLast->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
			{
				/*vector<CCarriage*> wag = GetWagons();
				if (wag.size())
				{
					auto car = wag.back();
					wag.pop_back();
					SetWagons(wag);
					this->removeChildByTag(car->getTag(), true);
				}*/
			}
				break;
			case ui::Widget::TouchEventType::ENDED:
				break;
			default:
				break;
			}
		});
		this->addChild(popLast, 100);

		auto train1 = CTrain::Create(CONSTANTS::TRAIN_SPRITE_FILENAME);
		train1->setAnchorPoint(Vec2(0, 0));
		train1->setPosition(Vec2(310, 45));
		this->addChild(train1, 100);

		tFlag = false;

	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
