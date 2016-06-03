#pragma once
#include <fstream>
#include "Constants.h"
#include <vector>

class CScoreSaver
{
public:
	CScoreSaver();
	~CScoreSaver();
	void SaveScore(std::string score);
	std::vector<int> GetHighScore();
};

