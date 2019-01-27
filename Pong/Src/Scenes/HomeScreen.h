#pragma once
#include "raylib.h"

namespace Scenes
{
	class HomeScreen final
	{
	private:

		const char* _header = "Pong";
		const char* _controls = "Use Arrow Keys to Move and Space to Launch the Ball";
		const char* _createdBy = "Made by Rud156";
		const char* _play = "Play";

		Color _button_color = RED;

		int _screen_width{};
		int _screen_height{};

		static HomeScreen* _instance;
		HomeScreen();

	public:
		static HomeScreen* Instance();
		static void setupScene();

		static bool drawAndCheckForGameStart();
	};
}
