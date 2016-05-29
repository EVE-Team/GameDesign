#include "StatisticsScene.h"
#include "BackGround.h"
#include "Constants.h"

Scene* CStatisticsScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = CStatisticsScene::create();

	layer->Init(scene);
	scene->addChild(layer);

	return scene;
}

bool CStatisticsScene::Init(Scene *scene)
{
	auto backGround = CBackGround::Create(CONSTANTS::BACKGROUND_FILENAME);
	this->addChild(backGround, 0);
	SetEventListener();
	CreateSceneLabels();

	return true;
}

void CStatisticsScene::CreateSceneLabels()
{
	auto header = Label::createWithTTF(CONSTANTS::STAT_CAPTION, CONSTANTS::FONT_NAME, 34);
	header->setPosition(Vec2(240, 280));
	header->setTag(1);
	this->addChild(header, 1);

	auto exitLabel = Label::createWithTTF(CONSTANTS::BACK_CAPTION, CONSTANTS::FONT_NAME, 20);
	exitLabel->setPosition(Vec2(240, 180));
	exitLabel->setTag(2);
	this->addChild(exitLabel, 1);
}

void CStatisticsScene::SetEventListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event){
		auto target = static_cast<Label*>(event->getCurrentTarget());
		target->setVisible(false);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

CStatisticsScene::CStatisticsScene()
{
}


CStatisticsScene::~CStatisticsScene()
{
}
