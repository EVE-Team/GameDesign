#pragma once
#include <string>

namespace CONSTANTS
{
	static const std::string FONT_NAME = "fonts/Marker Felt.ttf";
	static const std::string BACKGROUND_FILENAME_MAIN = "images/background.png";
	static const std::string BACKGROUND_FILENAME = "images/background2.png";
	static const std::string TITLE_PAUSE = "PAUSE";
	static const std::string GAME_NAME = "Train";
	static const std::string GAME_OVER = "Game Over!";
	static const std::string REPEAT_ACTION = "Want to play again - press Enter";
	static const std::string PAUSE_SPRITE_FILENAME = "pause.jpg";
	static const std::string START_GAME_CAPTION = "Start";
	static const std::string STAT_CAPTION = "High Score";
	static const std::string EXIT_CAPTION = "Exit";
	static const std::string BACK_CAPTION = "Back";
	static const std::string SCORE_TITLE = "score: ";
	static const int MAX_LEN = 9;
	static const int NUMBER_OF_HS_POS = 5;

	static const std::string TRAIN_SPRITE_FILENAME = "images/train.png";
	static const int NUMBER_OF_CARRIAGE = 6;	
	static const std::string CARRIAGE_SPRITE_FILENAME = "images/";
	static const std::string CARRIAGE_FILENAME_RESOLUTION = ".png";
	//static const std::string SCORE_FILENAME = ;
	static const std::string LIFES_IMAGE_FILENAME = "images/life.png";
	static const std::string PAUSE_BTN_IMG_FILENAME = "images/pause_button1.png";
	
	
	static const int RAIL_POSITON_Y = 78;

	namespace BASIC_POINTS
	{
		static const std::string FILENAME = "basicPoints.json";
		static const std::string NAME = "basicPoints";
		static const std::string X = "x";
		static const std::string Y = "y";
	};
};

class DataKeys
{
public :
	static const char* LIFE_COUNT_KEY;
	static const char* SCORE_COUNT_KEY;
	static const char* TRAIN_LEN_KEY;
};


struct MyPoint
{
	int x;
	int y;
};

