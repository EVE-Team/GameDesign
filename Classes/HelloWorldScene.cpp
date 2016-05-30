#include "HelloWorldScene.h"
#include "MainMenuScene.h"
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
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = CBackGround::Create(CONSTANTS::BACKGROUND_FILENAME);
	this->addChild(backGround, 0);
	InitBasicObjects();
	
	m_railTransport = CRailTransport::create();
	m_railTransport->BeginNewLevel(CONSTANTS::len);
	this->addChild(m_railTransport);
	return true;
}


void HelloWorld::InitBasicObjects()
{
	auto fileUtils = FileUtils::getInstance();
	string data = fileUtils->getStringFromFile(CONSTANTS::BASIC_POINTS::FILENAME);
	string err;
	auto  points = Json::parse(data, err);
	auto basicPoints = points[CONSTANTS::BASIC_POINTS::NAME].array_items();

	for (size_t i = 1; i <= CONSTANTS::NUMBER_OF_CARRIAGE; ++i)
	{
		auto carriage = CCarriage::Create(CONSTANTS::CARRIAGE_SPRITE_FILENAME + to_string(i) + CONSTANTS::CARRIAGE_FILENAME_RESOLUTION);
		carriage->setPosition(Vec2(basicPoints[i - 1][CONSTANTS::BASIC_POINTS::X].int_value(),
			basicPoints[i - 1][CONSTANTS::BASIC_POINTS::Y].int_value()));
		carriage->setTag(i);
		this->addChild(carriage, 1);
	}
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
