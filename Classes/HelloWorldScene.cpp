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

	auto backGround = CBackGround::Create(Constants::BACKGROUND_FILENAME_MAIN);
	this->addChild(backGround, 0);
	InitBasicObjects();
	
	m_railTransport = CRailTransport::create();
	m_railTransport->BeginNewLevel(UserDefault::getInstance()->getIntegerForKey(Constants::DataKeys::TRAIN_LEN_KEY));
	this->addChild(m_railTransport);

	m_scoreLabel = Label::createWithTTF(Constants::SCORE_TITLE +
		flatbuffers::NumToString(UserDefault::getInstance()->getIntegerForKey(Constants::DataKeys::SCORE_COUNT_KEY)),
		Constants::FONT_NAME, 16);
	m_scoreLabel->setColor(Color3B::YELLOW);
	m_scoreLabel->setAnchorPoint(Vec2(0, 0));
	m_scoreLabel->setPosition(Vec2(10, 30));
	this->addChild(m_scoreLabel, 1);

	m_lifesSprite = Sprite::create(Constants::LIFES_IMAGE_FILENAME);
	m_lifesSprite->setAnchorPoint(Vec2(0, 0));
	m_lifesSprite->setPosition(Vec2(85, 33));
	this->addChild(m_lifesSprite, 1);

	m_lifesLabel = Label::createWithTTF(flatbuffers::NumToString(UserDefault::getInstance()->getIntegerForKey(Constants::DataKeys::LIFE_COUNT_KEY)),
		Constants::FONT_NAME, 16);
	m_lifesLabel->setColor(Color3B::YELLOW);
	m_lifesLabel->setAnchorPoint(Vec2(0, 0));
	m_lifesLabel->setPosition(Vec2(105, 30));
	this->addChild(m_lifesLabel, 1);

	m_btnPause = CPauseButton::Create(Constants::PAUSE_BTN_IMG_FILENAME);
	m_btnPause->setPosition(Vec2(30, 290));
	this->addChild(m_btnPause, 1);

	return true;
}


void HelloWorld::InitBasicObjects()
{
	auto fileUtils = FileUtils::getInstance();
	string data = fileUtils->getStringFromFile(Constants::BasicPoints::FILENAME);
	string err;
	auto  points = Json::parse(data, err);
	auto basicPoints = points[Constants::BasicPoints::NAME].array_items();

	for (size_t i = 1; i <= Constants::NUMBER_OF_CARRIAGE; ++i)
	{
		auto carriage = CCarriage::Create(Constants::CARRIAGE_SPRITE_FILENAME + flatbuffers::NumToString(i) + Constants::CARRIAGE_FILENAME_RESOLUTION);
		carriage->setPosition(Vec2(basicPoints[i - 1][Constants::BasicPoints::X].int_value(),
			basicPoints[i - 1][Constants::BasicPoints::Y].int_value()));
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
	gameState->setTitleFontName(Constants::FONT_NAME);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	gameState->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + Constants::RAIL_POSITON_Y));
	int trainLen = UserDefault::getInstance()->getIntegerForKey(Constants::DataKeys::TRAIN_LEN_KEY);
	int score = UserDefault::getInstance()->getIntegerForKey(Constants::DataKeys::SCORE_COUNT_KEY);
	int lifes = UserDefault::getInstance()->getIntegerForKey(Constants::DataKeys::LIFE_COUNT_KEY);
	int state = 0;

	if (text == "You win")
	{
		score = score + 100 * trainLen;
		UserDefault::getInstance()->setIntegerForKey(Constants::DataKeys::SCORE_COUNT_KEY, score);
		if (trainLen < Constants::MAX_LEN)
		{
			title = "Next level";
			gameState->setTitleText(title);
			state = 2;			
			UserDefault::getInstance()->setIntegerForKey(Constants::DataKeys::TRAIN_LEN_KEY, ++trainLen);
		}
		else
		{
			state = 1;					
		}
	}
	else
	{
		UserDefault::getInstance()->setIntegerForKey(Constants::DataKeys::LIFE_COUNT_KEY, --lifes);
		if (lifes == 0)
		{		
			SaveResult();
			state = 3;
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
	if (m_scoreLabel && m_lifesLabel && m_lifesSprite && m_btnPause)
	{
		m_scoreLabel->setVisible(false);
		m_lifesLabel->setVisible(false);
		m_lifesSprite->setVisible(false);
		m_btnPause->RemoveListener();
		m_btnPause->setVisible(false);
	}	
	auto scoreLabel = Label::createWithTTF("Your score: " + flatbuffers::NumToString(score), Constants::FONT_NAME, 24);
	scoreLabel->setColor(Color3B::YELLOW);
	scoreLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 70));
	this->addChild(scoreLabel, 10);
}


void HelloWorld::SaveScore(const string& score)
{
	ofstream file;
	string path = FileUtils::getInstance()->getWritablePath() + Constants::Files::HIGH_SCORE;
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
	int trainLen = UserDefault::getInstance()->getIntegerForKey(Constants::DataKeys::TRAIN_LEN_KEY);
	int score = UserDefault::getInstance()->getIntegerForKey(Constants::DataKeys::SCORE_COUNT_KEY);
	int lifes = UserDefault::getInstance()->getIntegerForKey(Constants::DataKeys::LIFE_COUNT_KEY);
	ofstream file;
	string savesPath = FileUtils::getInstance()->getWritablePath() + Constants::Files::GAME_SAVES;
	file.open(savesPath);
	file << lifes << endl << trainLen << endl << score;
	file.close();
}