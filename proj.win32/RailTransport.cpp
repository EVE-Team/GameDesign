#include "RailTransport.h"

using namespace cocos2d;
using namespace std;


CRailTransport::CRailTransport()
{
}

CRailTransport::~CRailTransport()
{
}

CRailTransport* CRailTransport::create()
{
	auto layer = new (nothrow)CRailTransport();
	if (layer && layer->init())
	{
		layer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(layer);
		return nullptr;
	}	
	return layer;
}

bool CRailTransport::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setPosition(Vec2(400, CONSTANTS::RAIL_POSITON_Y));
	this->scheduleUpdate();
}

std::vector<int> CRailTransport::GetRandomArrayOfWagons(const int count)
{
	vector<int> points;
	while (points.size() != count)
	{
		int currRandom = rand() % CONSTANTS::NUMBER_OF_CARRIAGE + 1;
		points.push_back(currRandom);
	}
	return points;
}

void CRailTransport::BeginNewLevel(int length)
{
	m_length = length;
	this->m_levelCreatedTrain = GetRandomArrayOfWagons(length);
	auto train = Sprite::create(CONSTANTS::TRAIN_SPRITE_FILENAME);
	train->setAnchorPoint(Vec2(0, 0));
	Size trainSize = train->getContentSize();
	train->setPosition(Vec2(0, 0));

	this->addChild(train, 1);
	int startPosition = trainSize.width;
	for (size_t i = 0; i < m_levelCreatedTrain.size(); ++i)
	{
		auto newCarriage = Sprite::create(CONSTANTS::CARRIAGE_SPRITE_FILENAME + to_string(m_levelCreatedTrain[i]) + CONSTANTS::CARRIAGE_FILENAME_RESOLUTION);
		newCarriage->setAnchorPoint(Vec2(0, 0));
		newCarriage->setPosition(Vec2(startPosition, 0));
		newCarriage->setTag(m_levelCreatedTrain[i]);
		this->addChild(newCarriage);		
		Size carriageSize = newCarriage->getContentSize();
		startPosition += carriageSize.width;
	}
	auto carriageMove = MoveTo::create(4.0, Vec2(0 - startPosition, CONSTANTS::RAIL_POSITON_Y));
	this->runAction(carriageMove);
	m_trainRunningEndPos = -startPosition;
	m_isTrainRunning = true;
}

void CRailTransport::update(float delta)
{
	if ((this->getPositionX() == this->m_trainRunningEndPos) && (this->m_isTrainRunning))
	{
		this->removeAllChildrenWithCleanup(true);
		this->setPosition(Vec2(0, CONSTANTS::RAIL_POSITON_Y));
		this->scheduleUpdate();
		auto train = CTrain::Create(CONSTANTS::TRAIN_SPRITE_FILENAME);
		train->setAnchorPoint(Vec2(0, 0));
		train->setPosition(Vec2(10,0));
		this->addChild(train);
		m_isTrainRunning = false;
	}
}

void CRailTransport::AddWagon(const string& filename, int tag)
{
	auto newSprite = BackCarriage::Create(filename);
	m_shift += newSprite->getContentSize().width;
	newSprite->setPosition(Vec2(30 + m_shift,0));
	newSprite->setAnchorPoint(Vec2(0, 0));
	newSprite->setTag(tag);
	m_userCreatedTrain.push_back(tag);
	this->addChild(newSprite);
}

void CRailTransport::CheckGameState()
{
	bool right = true;
	if (m_userCreatedTrain.size() != m_levelCreatedTrain.size())
	{
		right = false;
	}
	else
	{
		for (size_t i = 0; i < m_levelCreatedTrain.size(); ++i)
		{
			int first = m_levelCreatedTrain[i];
			int second = m_userCreatedTrain[i];
			if (first != second)
			{
				right = false;
				break;
			}
		}
	}
	string text = right ? "You win" : "You lose";
	ShowState(text);
}

void CRailTransport::ShowState(const std::string& text)
{
	auto gameState = ui::Button::create();
	gameState->setTitleText(text);
	gameState->setColor(Color3B::YELLOW);
	gameState->setTitleFontSize(64);
	gameState->setTitleFontName(CONSTANTS::FONT_NAME);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	gameState->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	int length = m_length++;
	gameState->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			auto scene = HelloWorld::createScene();
			CONSTANTS::len++;
			Director::getInstance()->replaceScene(scene);
		}
		break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->addChild(gameState, 30);
}