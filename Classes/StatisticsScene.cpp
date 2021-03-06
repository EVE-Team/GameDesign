#include "StatisticsScene.h"
#include "BackGround.h"
#include "Constants.h"
#include "MainMenuScene.h"
#include "..\cocos2d\external\flatbuffers\util.h"
#include <fstream>

using namespace std;
using namespace cocos2d;

Scene* CStatisticsScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CStatisticsScene::create();
	scene->addChild(layer);
	return scene;
}

bool CStatisticsScene::init()
{
	auto backGround = CBackGround::Create(Constants::BACKGROUND_FILENAME);
	this->addChild(backGround, 0);
	SetEventListener();
	CreateSceneLabels();	
	auto scoreList = GetHighScore();
	int y = 20;
	for (auto &it : scoreList)
	{
		auto header = Label::createWithTTF(flatbuffers::NumToString(it), Constants::FONT_NAME,16 );
		header->setPosition(Vec2(240, 240 - y));
		header->setColor(Color3B::BLUE);
		y += 20;
		this->addChild(header);
	}
	return true;
}


void CStatisticsScene::CreateSceneLabels()
{
	auto header = Label::createWithTTF(Constants::STAT_CAPTION, Constants::FONT_NAME, 34);
	header->setPosition(Vec2(240, 280));
	header->setColor(Color3B::BLUE);
	this->addChild(header);
}

void CStatisticsScene::SetEventListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event){
		auto scene = CMainMenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


vector<int> CStatisticsScene::GetHighScore()
{
	ifstream file;
	string path = FileUtils::getInstance()->getWritablePath() + Constants::Files::HIGH_SCORE;
	file.open(path);
	string line;
	vector<int> temp;
	while (getline(file, line))
	{
		int num = atoi(line.c_str());
		if (num != 0)
		{
			temp.push_back(num);
		}
	}
	sort(temp.begin(), temp.end(), [](int i, int j){
		return i > j;
	});
	vector<int> res;
	for (size_t i = 0; i < temp.size() && i < Constants::NUMBER_OF_HS_POS; i++)
	{
		res.push_back(temp[i]);
	}
	return res;
}