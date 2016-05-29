#include "SequenceOfCarriage.h"
#include "cocos2d.h"
#include <random>
#include <json11.hpp>
#include "..\cocos2d\external\flatbuffers\util.h"
#include "Constants.h"

using namespace std;
using namespace cocos2d;
using namespace json11;

CSequenceOfCarriage::CSequenceOfCarriage()
{
	//FillBasicPoints();
}

CSequenceOfCarriage::~CSequenceOfCarriage()
{
}

void CSequenceOfCarriage::FillBasicPoints()
{
	auto fileUtils = FileUtils::getInstance();
	string data = fileUtils->getStringFromFile(CONSTANTS::BASIC_POINTS::FILENAME);
	string err;
	auto  points = Json::parse(data, err);
	auto basicPoints = points[CONSTANTS::BASIC_POINTS::NAME].array_items();
	for (auto const& it : basicPoints)
	{
		auto point = new MyPoint();
		point->x = it[CONSTANTS::BASIC_POINTS::X].int_value();
		point->y = it[CONSTANTS::BASIC_POINTS::Y].int_value();
		m_basicPoints.push_back(point);
	}
}

vector<int> CSequenceOfCarriage::Create(const int count)
{
	while (m_points.size() != count)
	{
		int currRandom = rand() % CONSTANTS::NUMBER_OF_CARRIAGE + 1;		
		m_points.push_back(currRandom);
	}
	return m_points;
}