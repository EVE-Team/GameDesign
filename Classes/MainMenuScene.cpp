#include "MainMenuScene.h"
#include "BackGround.h"
#include "HelloWorldScene.h"
#include "StatisticsScene.h"
#include "ui\CocosGUI.h"
#include "CONSTANTS.h"

Scene* CMainMenuScene::CreateScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = CMainMenuScene::create();

	layer->Init(scene);
	scene->addChild(layer);

	return scene;
}

bool CMainMenuScene::Init(Scene *scene)
{
	auto backGround = CBackGround::Create(CONSTANTS::SPLASH_BACKGROUND_FILENAME);
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

	auto btnNewGame = ui::Button::create();
	btnNewGame->setTitleText(CONSTANTS::START_GAME_CAPTION);
	btnNewGame->setColor(Color3B::BLUE);
	btnNewGame->setTitleFontSize(30);
	btnNewGame->setTitleFontName(CONSTANTS::FONT_NAME);
	btnNewGame->setPosition(Vec2(240, 240));
	btnNewGame->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
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
	this->addChild(btnNewGame);

	auto statisticsButton = ui::Button::create();
	statisticsButton->setTitleText(CONSTANTS::STAT_CAPTION);
	statisticsButton->setColor(Color3B::BLUE);
	statisticsButton->setTitleFontSize(30);
	statisticsButton->setTitleFontName(CONSTANTS::FONT_NAME);
	statisticsButton->setPosition(Vec2(240, 210));
	statisticsButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			{
				auto scene = CStatisticsScene::CreateScene();
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

	auto exitButton = ui::Button::create();
	exitButton->setTitleText(CONSTANTS::EXIT_CAPTION);
	exitButton->setColor(Color3B::BLUE);
	exitButton->setTitleFontSize(30);
	exitButton->setTitleFontName(CONSTANTS::FONT_NAME);
	exitButton->setPosition(Vec2(240, 180));
	exitButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			MenuCloseCallback(this);
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});

	this->addChild(exitButton);
}

void CMainMenuScene::MenuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

CMainMenuScene::CMainMenuScene()
{
}

CMainMenuScene::~CMainMenuScene()
{
}
