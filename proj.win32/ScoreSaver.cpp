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
	file.open(CONSTANTS::SCORE_FILENAME);
	file << score << endl;
}