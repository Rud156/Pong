#pragma once
#include "../Player/PlayerPaddle.h"

namespace Scenes
{
	class MainScene final
	{
	private:
		Player::PlayerPaddle* _humanPlayer;
		Player::PlayerPaddle* _aiPlayer;

		Common::Ball* _ball;

		int _screen_width;
		int _screen_height;

		int _human_player_score;
		int _ai_player_score;

		int _game_started;
		int _current_level;

		const int _max_countdown = 3;
		float _current_countdown = _max_countdown;

		const char* _first_play = "Game Starts In...";
		const char* _subsequent_play = "Next Game Start In...";

		static MainScene* _instance;
		MainScene();

		static void clearMemory();
		static bool countdownToGameStart();

		static void updateBall();
		static void createBall();

		static void updatePlayers();
		static void checkPaddleAndBallCollision();

		static void changeLevel();

	public:
		static MainScene* Instance();
		~MainScene();

		static void setupOrResetScene();
		static bool update();
	};
}
