#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "Carriage.h"
#include "Train.h"
#include <json11.hpp>
#include "ui\CocosGUI.h"
#include "..\cocos2d\external\flatbuffers\util.h"
#include "RailTransport.h"
#include "BackGround.h"
#include "Constants.h"
#include "BackCarriage.h"
#include "PauseButton.h"

using namespace cocos2d;
using namespace json11;
using namespace std;

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

	auto backGround = CBackGround::Create(CONSTANTS::BACKGROUND_FILENAME_MAIN);
	this->addChild(backGround, 0);
	InitBasicObjects();
	
	m_railTransport = CRailTransport::create();
	m_railTransport->BeginNewLevel(UserDefault::getInstance()->getIntegerForKey(DataKeys::TRAIN_LEN_KEY));
	this->addChild(m_railTransport);

	auto score = Label::createWithTTF(CONSTANTS::SCORE_TITLE + 
		flatbuffers::NumToString(UserDefault::getInstance()->getIntegerForKey(DataKeys::SCORE_COUNT_KEY)),
		CONSTANTS::FONT_NAME, 16);
	score->setColor(Color3B::YELLOW);	
	score->setAnchorPoint(Vec2(0, 0));
	score->setPosition(Vec2(10, 30));
	this->addChild(score, 1);

	auto life = Sprite::create(CONSTANTS::LIFES_IMAGE_FILENAME);	
	life->setAnchorPoint(Vec2(0, 0));
	life->setPosition(Vec2(85, 33));
	this->addChild(life, 1);

	auto nLife = Label::createWithTTF(flatbuffers::NumToString(UserDefault::getInstance()->getIntegerForKey(DataKeys::LIFE_COUNT_KEY)),
		CONSTANTS::FONT_NAME, 16);
	nLife->setColor(Color3B::YELLOW);
	nLife->setAnchorPoint(Vec2(0, 0));
	nLife->setPosition(Vec2(105, 30));
	this->addChild(nLife, 1);

	auto btnPause = CPauseButton::Create(CONSTANTS::PAUSE_BTN_IMG_FILENAME);
	btnPause->setPosition(Vec2(30, 290));
	this->addChild(btnPause, 1);

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


void HelloWorld::RemoveListenersForWagons()
{
	for (auto it : m_wagons)
	{
		it->RemoveListener();
	}
}


void HelloWorld::ShowState(const std::string& text)
{
	RemoveListenersForWagons();
	string title = text;
	auto gameState = ui::Button::create();
	gameState->setTitleText(text);
	gameState->setColor(Color3B::YELLOW);
	gameState->setTitleFontSize(64);
	gameState->setTitleFontName(CONSTANTS::FONT_NAME);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	gameState->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + CONSTANTS::RAIL_POSITON_Y));
	int trainLen = UserDefault::getInstance()->getIntegerForKey(DataKeys::TRAIN_LEN_KEY);
	int score = UserDefault::getInstance()->getIntegerForKey(DataKeys::SCORE_COUNT_KEY);
	int lifes = UserDefault::getInstance()->getIntegerForKey(DataKeys::LIFE_COUNT_KEY);
	int state = 0;

	if (text == "You win")
	{
		score = score + 100 * trainLen;
		UserDefault::getInstance()->setIntegerForKey(DataKeys::SCORE_COUNT_KEY, score);
		if (trainLen < CONSTANTS::MAX_LEN)
		{
			title = "Next level";
			gameState->setTitleText(title);
			state = 2;			
			UserDefault::getInstance()->setIntegerForKey(DataKeys::TRAIN_LEN_KEY, ++trainLen);
		}
		else
		{
			state = 1;					
		}
	}
	else
	{
		UserDefault::getInstance()->setIntegerForKey(DataKeys::LIFE_COUNT_KEY, --lifes);
		if (lifes == 0)
		{		
			SaveResult();
			state = 3;
			auto scoreLabel = Label::createWithTTF("Your score: " + flatbuffers::NumToString(score), CONSTANTS::FONT_NAME, 24);
			scoreLabel->setColor(Color3B::YELLOW);
			scoreLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 70));
			this->addChild(scoreLabel,10);
			SaveScore(flatbuffers::NumToString(score));
		}
		else
		{
			title = "Try again";
			gameState->setTitleText(title);
			state = 2;				
		}
	}
	if ((state == 1) || (state == 3))
	{
		gameState->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
			{
				auto scene = CMainMenuScene::createScene();
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


void HelloWorld::SaveScore(const string& score)
{
	ofstream file;
	string path = FileUtils::getInstance()->getWritablePath() + "/score.db";
	file.open(path, ios::app);
	file << score << endl;
	file.close();
}


void HelloWorld::onExit()
{
	SaveResult();
	Layer::onExit();
}


void HelloWorld::SaveResult()
{
	int trainLen = UserDefault::getInstance()->getIntegerForKey(DataKeys::TRAIN_LEN_KEY);
	int score = UserDefault::getInstance()->getIntegerForKey(DataKeys::SCORE_COUNT_KEY);
	int lifes = UserDefault::getInstance()->getIntegerForKey(DataKeys::LIFE_COUNT_KEY);
	ofstream file;
	string savesPath = FileUtils::getInstance()->getWritablePath() + "/saves.db";
	file.open(savesPath);
	file << lifes << endl << trainLen << endl << score;
	file.close();
}