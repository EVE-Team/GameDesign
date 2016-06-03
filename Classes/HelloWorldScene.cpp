#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "Carriage.h"
#include "Train.h"
#include <json11.hpp>
#include "ui\CocosGUI.h"
#include "..\cocos2d\external\flatbuffers\util.h"
#include "RailTransport.h"
#include "ScoreSaver.h"


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
	score->setPosition(Vec2(10, 300));
	this->addChild(score, 1);

	auto life = Sprite::create("images\\life.png");
	life->setScale(0.03);
	life->setAnchorPoint(Vec2(0, 0));
	life->setPosition(Vec2(90, 305));
	this->addChild(life, 1);

	auto nLife = Label::createWithTTF(flatbuffers::NumToString(CONSTANTS::number_life), CONSTANTS::FONT_NAME, 16);
	nLife->setColor(Color3B::YELLOW);
	nLife->setAnchorPoint(Vec2(0, 0));
	nLife->setPosition(Vec2(100, 300));
	this->addChild(nLife, 1);

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
		auto carriage = CCarriage::Create(CONSTANTS::CARRIAGE_SPRITE_FILENAME + flatbuffers::NumToString(i) + CONSTANTS::CARRIAGE_FILENAME_RESOLUTION);
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
		CONSTANTS::score = CONSTANTS::score +  100 * CONSTANTS::len;
		if (CONSTANTS::len < CONSTANTS::MAX_LEN)
		{
			title = "Next level";
			gameState->setTitleText(title);
			CONSTANTS::state = 2;
			CONSTANTS::len++;
		}
		else
		{
			CONSTANTS::state = 1;
		}
	}
	else
	{
		if (CONSTANTS::number_life == 1)
		{
			CONSTANTS::state = 3;
			CScoreSaver saver;
			saver.SaveScore(flatbuffers::NumToString(CONSTANTS::score));
			CONSTANTS::score = 0;
			CONSTANTS::number_life = 3;
		}
		else
		{
			title = "Try again";
			gameState->setTitleText(title);
			CONSTANTS::state = 2;
			CONSTANTS::number_life--;
		}
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
