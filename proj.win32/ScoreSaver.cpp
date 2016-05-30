#include "ScoreSaver.h"

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

vector<string> CScoreSaver::GetScore()
{
	ifstream file;
	file.open(CONSTANTS::SCORE_FILENAME);
	string line;
	vector<string> temp;
	while (getline(file, line))
	{
		temp.push_back(line);
	}
	return temp;
}