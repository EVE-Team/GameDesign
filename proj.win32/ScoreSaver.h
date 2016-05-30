#pragma once
#include <fstream>
#include "Constants.h"

class CScoreSaver
{
public:
	CScoreSaver();
	~CScoreSaver();
	void SaveScore(std::string score);
};

