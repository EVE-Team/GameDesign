#include "MainMenuScene.h"
#include "BackGround.h"
#include "HelloWorldScene.h"
#include "StatisticsScene.h"
#include "ui\CocosGUI.h"
#include "Constants.h"
#include <fstream>

using namespace cocos2d;
using namespace std;

Scene* CMainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CMainMenuScene::create();	
	scene->addChild(layer);
	return scene;
}

bool CMainMenuScene::init()
{
	auto backGround = CBackGround::Create(CONSTANTS::BACKGROUND_FILENAME);
	this->addChild(backGround, 0);
	CreateSceneLabels();
	return true;
}

void CMainMenuScene::CreateSceneLabels()
{
	auto name = Label::createWithTTF(CONSTANTS::GAME_NAME, CONSTANTS::FONT_NAME, 34);
	name->setPosition(Vec2(240, 280));
	name->setTag(1);
	this->addChild(name, 1);
	int shift = 0;
	auto btnNewGame = ui::Button::create();
	btnNewGame->setTitleText(CONSTANTS::START_GAME_CAPTION);
	btnNewGame->setColor(Color3B::BLUE);
	btnNewGame->setTitleFontSize(30);
	btnNewGame->setTitleFontName(CONSTANTS::FONT_NAME);
	btnNewGame->setPosition(Vec2(240, 240 - shift));
	btnNewGame->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			{
				UserDefault::getInstance()->setIntegerForKey(DataKeys::SCORE_COUNT_KEY, 0);
				UserDefault::getInstance()->setIntegerForKey(DataKeys::TRAIN_LEN_KEY, 3);
				UserDefault::getInstance()->setIntegerForKey(DataKeys::LIFE_COUNT_KEY, 3);
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
	this->addChild(btnNewGame);
	shift += 30;

	ifstream file;
	string savesPath = FileUtils::getInstance()->getWritablePath() + "/saves.db";
	file.open(savesPath);
	int score, lifes, trainLen;
	if (file >> lifes && file >> trainLen && file >> score)
	{
		if (lifes > 0)
		{
			UserDefault::getInstance()->setIntegerForKey(DataKeys::SCORE_COUNT_KEY, score);
			UserDefault::getInstance()->setIntegerForKey(DataKeys::TRAIN_LEN_KEY, trainLen);
			UserDefault::getInstance()->setIntegerForKey(DataKeys::LIFE_COUNT_KEY, lifes);
			auto btnResume = ui::Button::create();
			btnResume->setTitleText(CONSTANTS::TITLE_RESUME_GAME);
			btnResume->setColor(Color3B::BLUE);
			btnResume->setTitleFontSize(30);
			btnResume->setTitleFontName(CONSTANTS::FONT_NAME);
			btnResume->setPosition(Vec2(240, 240 - shift));
			btnResume->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
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
			this->addChild(btnResume);
			shift += 30;
		}
	}	

	auto statisticsButton = ui::Button::create();
	statisticsButton->setTitleText(CONSTANTS::STAT_CAPTION);
	statisticsButton->setColor(Color3B::BLUE);
	statisticsButton->setTitleFontSize(30);
	statisticsButton->setTitleFontName(CONSTANTS::FONT_NAME);
	statisticsButton->setPosition(Vec2(240, 240 - shift));
	statisticsButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			{
				auto scene = CStatisticsScene::createScene();
				Director::getInstance()->replaceScene(scene);
			}			
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(statisticsButton);
	shift += 30;

	auto exitButton = ui::Button::create();
	exitButton->setTitleText(CONSTANTS::EXIT_CAPTION);
	exitButton->setColor(Color3B::BLUE);
	exitButton->setTitleFontSize(30);
	exitButton->setTitleFontName(CONSTANTS::FONT_NAME);
	exitButton->setPosition(Vec2(240, 240 - shift));
	exitButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			Director::getInstance()->end();
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
						exit(0);
			#endif
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});

	this->addChild(exitButton);
}
