#include "MainMenuScene.h"
#include "Resources.h"
#include "BackGround.h"
#include "StatisticsScene.h"

Scene* CMainMenuScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = CMainMenuScene::create();

	layer->Init(scene);
	scene->addChild(layer);

	return scene;
}

bool CMainMenuScene::Init(Scene *scene)
{
	auto backGround = CBackGround::Create(splashBackGroundFileName);
	this->addChild(backGround, 0);
	SetEventListener();
	CreateSceneLabels();

	return true;
}

void CMainMenuScene::CreateSceneLabels()
{
	auto name = Label::createWithTTF(gameName, fontName, 34);
	name->setPosition(Vec2(240, 280));
	name->setTag(1);
	this->addChild(name, 1);

	auto startLabel = Label::createWithTTF(startGameText, fontName, 20);
	startLabel->setPosition(Vec2(240, 240));
	startLabel->setTag(2);
	this->addChild(startLabel, 1);

	auto statisticsLabel = Label::createWithTTF(statisticsText, fontName, 20);
	statisticsLabel->setPosition(Vec2(240, 210));
	statisticsLabel->setTag(3);
	this->addChild(statisticsLabel, 1);

	auto exitLabel = Label::createWithTTF(exitGameText, fontName, 20);
	exitLabel->setPosition(Vec2(240, 180));
	exitLabel->setTag(4);
	this->addChild(exitLabel, 1);
}

void CMainMenuScene::SetEventListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [](Touch* touch, Event* event){
		auto target = static_cast<Label*>(event->getCurrentTarget());
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
	case 4: MenuCloseCallback(); break;
	}
}

void CMainMenuScene::ShowStatistics()
{
	//auto scene = CStatisticsScene::CreateScene();
}

void CMainMenuScene::MenuCloseCallback()
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
