#include "GameScene.h"
#include "BackGround.h"
#include "Constants.h"

Scene* CGameScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = CGameScene::create();

	layer->Init(scene);
	scene->addChild(layer);

	return scene;
}

bool CGameScene::Init(Scene *scene)
{
	auto backGround = CBackGround::Create(CONSTANTS::SPLASH_BACKGROUND_FILENAME);
	this->addChild(backGround, 0);
	SetEventListener();
	CreateSceneLabels();

	return true;
}

void CGameScene::CreateSceneLabels()
{
	auto name = Label::createWithTTF(CONSTANTS::GAME_NAME, CONSTANTS::FONT_NAME, 34);
	name->setPosition(Vec2(240, 280));
	name->setTag(1);
	this->addChild(name, 1);

	auto startLabel = Label::createWithTTF(CONSTANTS::START_GAME_CAPTION, CONSTANTS::FONT_NAME, 20);
	startLabel->setPosition(Vec2(240, 240));
	startLabel->setTag(2);
	this->addChild(startLabel, 1);

	auto statisticsLabel = Label::createWithTTF(CONSTANTS::STAT_CAPTION, CONSTANTS::FONT_NAME, 20);
	statisticsLabel->setPosition(Vec2(240, 210));
	statisticsLabel->setTag(3);
	this->addChild(statisticsLabel, 1);

	auto exitLabel = Label::createWithTTF(CONSTANTS::EXIT_CAPTION, CONSTANTS::FONT_NAME, 20);
	exitLabel->setPosition(Vec2(240, 180));
	exitLabel->setTag(4);
	this->addChild(exitLabel, 1);
}

void CGameScene::SetEventListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [](Touch* touch, Event* event){
		auto target = static_cast<Label*>(event->getCurrentTarget());
		target->setVisible(false);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
}
