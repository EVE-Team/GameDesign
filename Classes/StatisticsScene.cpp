#include "StatisticsScene.h"
#include "BackGround.h"
#include "Constants.h"
#include "MainMenuScene.h"
#include "ScoreSaver.h"
#include "..\cocos2d\external\flatbuffers\util.h"

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

	CScoreSaver saver;
	auto scoreList = saver.GetHighScore();
	int y = 20;
	for (auto &it : scoreList)
	{
		auto header = Label::createWithTTF(flatbuffers::NumToString(it), CONSTANTS::FONT_NAME,16 );
		header->setPosition(Vec2(240, 240 - y));
		header->setColor(Color3B::BLUE);
		y += 20;
		this->addChild(header);
	}
	return true;
}


void CStatisticsScene::CreateSceneLabels()
{
	auto header = Label::createWithTTF(CONSTANTS::STAT_CAPTION, CONSTANTS::FONT_NAME, 34);
	header->setPosition(Vec2(240, 280));
	header->setColor(Color3B::BLUE);
	this->addChild(header, 1);
	/*auto exitLabel = Label::createWithTTF(CONSTANTS::BACK_CAPTION, CONSTANTS::FONT_NAME, 20);
	exitLabel->setPosition(Vec2(240, 50));
	header->setColor(Color3B::YELLOW);
	this->addChild(exitLabel, 1);*/
}

void CStatisticsScene::SetEventListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event){
		auto scene = CMainMenuScene::CreateScene();
		Director::getInstance()->replaceScene(scene);
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
