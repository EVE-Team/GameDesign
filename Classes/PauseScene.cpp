#include "PauseScene.h"
#include "BackGround.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "ui\CocosGUI.h"
#include "Constants.h"

using namespace cocos2d;
using namespace std;

Scene* CPauseScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CPauseScene::create();
	scene->addChild(layer);
	return scene;
}

bool CPauseScene::init()
{
	auto backGround = CBackGround::Create(CONSTANTS::BACKGROUND_FILENAME);
	this->addChild(backGround, 0);
	CreateSceneLabels();
	return true;
}

void CPauseScene::CreateSceneLabels()
{
	auto name = Label::createWithTTF(CONSTANTS::TITLE_PAUSE, CONSTANTS::FONT_NAME, 64);
	name->setPosition(Vec2(240, 280));
	name->setTag(1);
	this->addChild(name, 1);

	auto btnNewGame = ui::Button::create();
	btnNewGame->setTitleText("RESUME");
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
	statisticsButton->setTitleText("TO MENU");
	statisticsButton->setColor(Color3B::BLUE);
	statisticsButton->setTitleFontSize(30);
	statisticsButton->setTitleFontName(CONSTANTS::FONT_NAME);
	statisticsButton->setPosition(Vec2(240, 210));
	statisticsButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
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

	this->addChild(statisticsButton);
}
