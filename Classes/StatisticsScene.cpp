#include "StatisticsScene.h"
#include "Resources.h"
#include "BackGround.h"

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
	auto backGround = CBackGround::Create(splashBackGroundFileName);
	this->addChild(backGround, 0);
	SetEventListener();
	CreateSceneLabels();

	return true;
}

void CStatisticsScene::CreateSceneLabels()
{
	auto header = Label::createWithTTF(statisticsText, fontName, 34);
	header->setPosition(Vec2(240, 280));
	header->setTag(1);
	this->addChild(header, 1);

	auto exitLabel = Label::createWithTTF(backStepText, fontName, 20);
	exitLabel->setPosition(Vec2(240, 180));
	exitLabel->setTag(2);
	this->addChild(exitLabel, 1);
}

void CStatisticsScene::SetEventListener()
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

CStatisticsScene::CStatisticsScene()
{
}


CStatisticsScene::~CStatisticsScene()
{
}
