#pragma once

class Constants
{
public:
	static const char* FONT_NAME;
	
	static const char* TITLE_PAUSE;
	static const char* GAME_NAME;
	static const char* GAME_OVER;
	static const char* PAUSE_SPRITE_FILENAME;
	static const char* START_GAME_CAPTION;
	static const char* TITLE_RESUME_GAME;
	static const char* STAT_CAPTION;
	static const char* EXIT_CAPTION;
	static const char* BACK_CAPTION;
	static const char* SCORE_TITLE;
	

	static const char* TRAIN_SPRITE_FILENAME;
	static const char* BACKGROUND_FILENAME_MAIN;
	static const char* BACKGROUND_FILENAME;
	static const char* CARRIAGE_SPRITE_FILENAME;
	static const char* CARRIAGE_FILENAME_RESOLUTION;
	static const char* LIFES_IMAGE_FILENAME;
	static const char* PAUSE_BTN_IMG_FILENAME;
	
	static const int MAX_LEN;
	static const int NUMBER_OF_HS_POS;
	static const int RAIL_POSITON_Y;
	static const int NUMBER_OF_CARRIAGE;

	class BasicPoints
	{
	public:
		static const char* FILENAME;
		static const char* NAME;
		static const char* X;
		static const char* Y;
	};

	class DataKeys
	{
	public:
		static const char* LIFE_COUNT_KEY;
		static const char* SCORE_COUNT_KEY;
		static const char* TRAIN_LEN_KEY;
	};

	class Files
	{
	public:
		static const char* GAME_SAVES;
		static const char* HIGH_SCORE;
	};
};
