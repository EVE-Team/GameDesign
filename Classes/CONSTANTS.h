#pragma once
#include <string>

namespace CONSTANTS
{
	static const std::string FONT_NAME = "fonts/Marker Felt.ttf";
	static const std::string BACKGROUND_FILENAME = "images/background.png";	
	static const std::string FIRST_ACTION = "Let's Play! Touch the screen!";
	static const std::string GAME_NAME = "Train";
	static const std::string GAME_OVER = "Game Over!";
	static const std::string REPEAT_ACTION = "Want to play again - press Enter";
	static const std::string PAUSE_SPRITE_FILENAME = "pause.jpg";
	static const std::string START_GAME_CAPTION = "Start";
	static const std::string STAT_CAPTION = "High Score";
	static const std::string EXIT_CAPTION = "Exit";
	static const std::string BACK_CAPTION = "Back";
	static const int MAX_LEN = 9;
	static const int NUMBER_OF_HS_POS = 5;

	static const std::string TRAIN_SPRITE_FILENAME = "images/train.png";
	static const int NUMBER_OF_CARRIAGE = 6;	
	static const std::string CARRIAGE_SPRITE_FILENAME = "images/";
	static const std::string CARRIAGE_FILENAME_RESOLUTION = ".png";
	//static const std::string SCORE_FILENAME = ;
	extern int len;
	extern int state;
	extern int score;
	extern int number_life;
	static const int RAIL_POSITON_Y = 78;

	namespace BASIC_POINTS
	{
		static const std::string FILENAME = "basicPoints.json";
		static const std::string NAME = "basicPoints";
		static const std::string X = "x";
		static const std::string Y = "y";
	};
};


struct MyPoint
{
	int x;
	int y;
};

