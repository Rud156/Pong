#pragma once
#include "raylib.h"
#include <string>

namespace Scenes
{
	class GameOver final
	{
	private:
		int _screen_width;
		int _screen_height;

		const char* _survived_text = "Level Reached";
		const char* _replay_text = "Replay";

		int _level_count;
		std::string _level_text;

		Color _button_color;

		static GameOver* _instance;
		GameOver();

	public:
		static GameOver* Instance();
		static void setupScene();

		static bool updateScene();

		static void setLevelCount(int levelCount);
	};
}
