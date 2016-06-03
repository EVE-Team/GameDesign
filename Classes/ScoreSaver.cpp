#include "ScoreSaver.h"
#include <algorithm>

using namespace std;

CScoreSaver::CScoreSaver()
{
}


CScoreSaver::~CScoreSaver()
{
}


void CScoreSaver::SaveScore(string score)
{
	ofstream file;
	file.open(CONSTANTS::SCORE_FILENAME,ios::app);
	file << score << endl;
	file.close();
}

vector<int> CScoreSaver::GetHighScore()
{
	ifstream file;
	file.open(CONSTANTS::SCORE_FILENAME);
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