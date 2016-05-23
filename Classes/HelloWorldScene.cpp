#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "CSequenceOfMine.h"
#include "SequenceOfCarriage.h"
#include "Point.h"
#include "Carriage.h"
#include "Train.h"
#include <json11.hpp>
#include "..\cocos2d\external\flatbuffers\util.h"

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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = CBackGround::Create(CONSTANTS::SEA_SPRITE_FILENAME);
	this->addChild(backGround, 0);

	Size carriageSize;

	auto carriage1 = CCarriage::Create(CONSTANTS::CARRIAGE1_SPRITE_FILENAME);
	carriage1->setPosition(Vec2(60, 280));
	carriage1->setAnchorPoint(Vec2(0, 0));
	carriage1->setTag(1);
	carriageSize = carriage1->getContentSize();
	this->addChild(carriage1, 1);

	auto carriage2 = CCarriage::Create(CONSTANTS::CARRIAGE2_SPRITE_FILENAME);
	carriage2->setPosition(Vec2(180, 280));
	carriage2->setTag(2);
	this->addChild(carriage2, 1);

	auto carriage3 = CCarriage::Create(CONSTANTS::CARRIAGE3_SPRITE_FILENAME);
	carriage3->setPosition(Vec2(300, 280));
	carriage3->setTag(3);
	this->addChild(carriage3, 1);

	auto carriage4 = CCarriage::Create(CONSTANTS::CARRIAGE4_SPRITE_FILENAME);
	carriage4->setPosition(Vec2(420, 280));
	carriage4->setTag(4);
	this->addChild(carriage4, 1);

	auto carriage5 = CCarriage::Create(CONSTANTS::CARRIAGE5_SPRITE_FILENAME);
	carriage5->setPosition(Vec2(60, 200));
	carriage5->setTag(5);
	this->addChild(carriage5, 1);

	auto carriage6 = CCarriage::Create(CONSTANTS::CARRIAGE6_SPRITE_FILENAME);
	carriage6->setPosition(Vec2(180, 200));
	carriage6->setTag(6);
	this->addChild(carriage6, 1);

	auto carriage7 = CCarriage::Create(CONSTANTS::CARRIAGE7_SPRITE_FILENAME);
	carriage7->setPosition(Vec2(300, 200));
	carriage7->setTag(7);
	this->addChild(carriage7, 1);

	auto carriage8 = CCarriage::Create(CONSTANTS::CARRIAGE8_SPRITE_FILENAME);
	carriage8->setPosition(Vec2(420, 200));
	carriage8->setTag(8);
	this->addChild(carriage8, 1);

	auto train = CTrain::Create(CONSTANTS::TRAIN_SPRITE_FILENAME);
	train->setAnchorPoint(Vec2(0, 0));
	Size trainSize = train->getContentSize();
	train->setPosition(Vec2(0 - trainSize.width, 50));
	this->addChild(train, 1);

	auto move = MoveTo::create(8.0, Vec2(600, 50));
	//train->runAction(move);

	auto seq = &CSequenceOfCarriage::CSequenceOfCarriage();
	auto vec = seq->Create(5);

	int shift = 10;
	int startPosition = 0 - trainSize.width - shift;

	for (int i = 0; i < vec.size(); ++i)
	{
		startPosition -= carriageSize.width;
		auto newCarriage = CCarriage::Create(CONSTANTS::CARRIAGE_SPRITE_FILENAME + to_string(vec[i]) + CONSTANTS::CARRIAGE_FILENAME_RESOLUTION);
		newCarriage->setAnchorPoint(Vec2(0, 0));
		newCarriage->setPosition(Vec2(startPosition, 50));
		newCarriage->setTag(vec[i]);
		startPosition -= shift;
		auto carriageMove = MoveTo::create(8.0, Vec2(600, 50));
		newCarriage->runAction(carriageMove);
		this->addChild(newCarriage, 1);
		m_wagons.push_back(newCarriage);
	}

	this->scheduleUpdate();

	train->setPosition(Vec2(300, 50));
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

vector<CCarriage*> HelloWorld::GetWagons()
{
	return m_toFill;
}

vector<CCarriage*> HelloWorld::GetBasicWagons()
{
	return m_wagons;
}

void HelloWorld::SetWagons(vector<CCarriage*> wagons)
{
	this->m_toFill = wagons;
}

void HelloWorld::update(float delta)
{
	/*for (size_t i = 0; i < bombs.size(); ++i)
	{
		if (bombs[i]->isVisible())
		{
			return;
		}
	}
	auto scene = CMainMenuScene::CreateScene();
	Director::getInstance()->replaceScene(scene);*/
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
