#pragma once
#include "cocos2d.h"
#include "BackCarriage.h"

class CRailTransport : public cocos2d::Layer
{
public:
	CRailTransport();
	~CRailTransport();
	void BeginNewLevel(int length);
	static CRailTransport* create();
	virtual bool init();
	void update(float delta);
	void CheckGameState();
	void RemoveListenersForWagons();

	std::vector<int> m_levelCreatedTrain;
	std::vector<int> m_userCreatedTrain;
	std::vector<BackCarriage*> m_wagons;
	void AddWagon(const std::string& filename, int tag);
	float m_shift = 0;
private:
	std::vector<int> GetRandomArrayOfWagons(const int length);
	int m_trainRunningEndPos			= 0;
	bool m_isTrainRunning				= false;
	int m_length;
};

