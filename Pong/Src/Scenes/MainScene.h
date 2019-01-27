#pragma once
#include "../Player/PlayerPaddle.h"
#include <string>

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
		const int _ai_paddle_speed_increment_amount = 50;

		const int _max_countdown = 3;
		float _current_countdown = _max_countdown;

		const char* _first_play = "Game Starts In...";
		const char* _subsequent_play = "Next Game Start In...";
		const std::string _player_health = "Player Lives";

		static MainScene* _instance;
		MainScene();

		static void clearMemory();
		static bool countdownToGameStart();

		static void displayScore();

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
