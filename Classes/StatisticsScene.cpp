#include "StatisticsScene.h"
#include "BackGround.h"
#include "Constants.h"
#include "MainMenuScene.h"
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
	auto scoreList = GetHighScore();
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
	this->addChild(header);
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

vector<int> CStatisticsScene::GetHighScore()
{
	ifstream file;
	file.open(CCFileUtils::getInstance() ->fullPathForFilename("score.db").c_str());
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
	for (size_t i = 0; i < temp.size() && i < CONSTANTS::NUMBER_OF_HS_POS; i++)
	{
		res.push_back(temp[i]);
	}
	return res;
}