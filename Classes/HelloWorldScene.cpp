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
	FillBasicPoints();

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = CBackGround::Create(CONSTANTS::BACKGROUND_FILENAME);
	this->addChild(backGround, 0);

	Size carriageSize;

	for (size_t i = 1; i < 7; ++i)
	{
		auto carriage = CCarriage::Create(CONSTANTS::CARRIAGE_SPRITE_FILENAME + to_string(i) + CONSTANTS::CARRIAGE_FILENAME_RESOLUTION);
		carriage->setPosition(Vec2(m_basicPoints[i-1]->x, m_basicPoints[i-1]->y));
		carriage->setTag(i);
		carriageSize = carriage->getContentSize();
		this->addChild(carriage, 1);
	}
	CreateRailTransport();

	this->scheduleUpdate();
	return true;
}

void HelloWorld::CreateRailTransport()
{
	auto seq = &CSequenceOfCarriage::CSequenceOfCarriage();
	auto vec = seq->Create(3);

	a = CRailTransport::create();
	a->setPosition(Vec2(400, CONSTANTS::RAIL_POSITON_Y));
	this->addChild(a, 20);

	auto train = CTrain::Create(CONSTANTS::TRAIN_SPRITE_FILENAME);
	train->setAnchorPoint(Vec2(0, 0));
	Size trainSize = train->getContentSize();
	train->setPosition(Vec2(0, 0));

	a->addChild(train, 1);

	int startPosition = trainSize.width;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		auto newCarriage = Sprite::create(CONSTANTS::CARRIAGE_SPRITE_FILENAME + to_string(vec[i]) + CONSTANTS::CARRIAGE_FILENAME_RESOLUTION);
		newCarriage->setAnchorPoint(Vec2(0, 0));
		newCarriage->setPosition(Vec2(startPosition, 0));
		newCarriage->setTag(vec[i]);
		a->addChild(newCarriage, 1);
		m_wagons.push_back(newCarriage);
		Size carriageSize = newCarriage->getContentSize();
		startPosition += carriageSize.width;
	}
	carriageMove = MoveTo::create(4.0, Vec2(0 - startPosition, CONSTANTS::RAIL_POSITON_Y));
	a->runAction(carriageMove);
	this->trainRunningEndPos = -startPosition;
	this->IsTrainRunning = true;
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

vector<Sprite*> HelloWorld::GetBasicWagons()
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

void HelloWorld::update(float delta)
{
	if ((a->getPositionX() == this->trainRunningEndPos) && (this->IsTrainRunning))
	{		
		auto train = CTrain::Create(CONSTANTS::TRAIN_SPRITE_FILENAME);
		train->setAnchorPoint(Vec2(0, 0));
		train->setPosition(Vec2(10, CONSTANTS::RAIL_POSITON_Y));
		this->addChild(train, 100);
		IsTrainRunning = false;
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
