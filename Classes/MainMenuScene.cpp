#include "MainMenuScene.h"
#include "Resources.h"
#include "BackGround.h"
#include "StatisticsScene.h"
#include "ui\CocosGUI.h"

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
	auto backGround = CBackGround::Create(splashBackGroundFileName);
	this->addChild(backGround, 0);
	//SetEventListener();
	CreateSceneLabels();

	return true;
}

void CMainMenuScene::CreateSceneLabels()
{
	auto name = Label::createWithTTF(gameName, fontName, 34);
	name->setPosition(Vec2(240, 280));
	name->setTag(1);
	this->addChild(name, 1);

	auto startLabel = Label::createWithTTF(startGameText, fontName, 30);
	startLabel->setPosition(Vec2(240, 240));
	startLabel->setTag(2);
	this->addChild(startLabel, 1);

	/*auto statisticsLabel = Label::createWithTTF(statisticsText, fontName, 30);
	statisticsLabel->setPosition(Vec2(240, 210));
	statisticsLabel->setTag(3);
	this->addChild(statisticsLabel, 1);*/

	auto statisticsButton = ui::Button::create();
	statisticsButton->setTitleText(statisticsText);
	statisticsButton->setColor(Color3B::BLUE);
	statisticsButton->setTitleFontSize(30);
	statisticsButton->setTitleFontName(fontName);
	statisticsButton->setPosition(Vec2(240, 210));
	statisticsButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
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

	this->addChild(statisticsButton);

	auto exitButton = ui::Button::create();
	exitButton->setTitleText(exitGameText);
	exitButton->setColor(Color3B::BLUE);
	exitButton->setTitleFontSize(30);
	exitButton->setTitleFontName(fontName);
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

void CMainMenuScene::SetEventListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [](Touch* touch, Event* event){
		auto target = static_cast<Label*>(event->getCurrentTarget());
		if (target->getPhysicsBody()->getTag() == 6)
		{
			int i = 0;
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

void CMainMenuScene::ChooseAction(int action)
{
	switch (action)
	{
	case 2: break;
	case 3: break;
	case 4: break;
	}
}

void CMainMenuScene::ShowStatistics()
{
	auto scene = CStatisticsScene::CreateScene();
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
