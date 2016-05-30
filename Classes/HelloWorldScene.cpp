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

	auto score = Label::createWithTTF("score: " + flatbuffers::NumToString(CONSTANTS::score), CONSTANTS::FONT_NAME, 16);
	score->setColor(Color3B::YELLOW);	
	score->setAnchorPoint(Vec2(0, 0));
	score->setPosition(Vec2(30, 300));
	this->addChild(score, 1);

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
		m_wagons.push_back(carriage);
		this->addChild(carriage, 1);
	}
}

void HelloWorld::SetListenersForWagons()
{
	for (auto it : m_wagons)
	{
		it->SetContactListener();
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

void HelloWorld::ShowState(const std::string& text)
{
	string title = text;
	auto gameState = ui::Button::create();
	gameState->setTitleText(text);
	gameState->setColor(Color3B::YELLOW);
	gameState->setTitleFontSize(64);
	gameState->setTitleFontName(CONSTANTS::FONT_NAME);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	gameState->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + CONSTANTS::RAIL_POSITON_Y));
	int length = m_length++;
	if (text == "You win")
	{
		if (CONSTANTS::len < CONSTANTS::MAX_LEN)
		{
			title = "Next level";
			gameState->setTitleText(title);
			CONSTANTS::state = 2;
		}
		else
		{
			CONSTANTS::state = 1;
		}
	}
	else
	{
		CONSTANTS::state = 3;
	}
	if ((CONSTANTS::state == 1) || (CONSTANTS::state == 3))
	{
		CONSTANTS::len = 3;
		gameState->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
			{
				auto scene = CMainMenuScene::CreateScene();
				Director::getInstance()->replaceScene(scene);				
			}
			break;
			case ui::Widget::TouchEventType::ENDED:
				break;
			default:
				break;
			}
		});
	}
	else
	{
		CONSTANTS::len++;
		gameState->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
			{				
				auto scene = HelloWorld::createScene();
				Director::getInstance()->replaceScene(scene);
			}
			break;
			case ui::Widget::TouchEventType::ENDED:
				break;
			default:
				break;
			}
		});
	}
	
	this->addChild(gameState, 30);
}
