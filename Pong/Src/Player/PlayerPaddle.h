#pragma once

#include <string>
#include "raylib.h"
#include "../Enums/Enums.h"
#include "../Common/Ball.h"

namespace Player
{
	class PlayerPaddle
	{
	private:
		std::string _player_name;

		int _window_width;
		int _window_height;

		Vector2 _spawn_position{};
		Vector2 _position{};
		Vector2 _velocity{};

		Color _color{};
		const int _paddle_width = 20;
		const int _paddle_height = 5;

		bool _game_started{};
		int _movement_speed = 5;
		bool is_ai;

		Common::Ball* _ball{};

		void movePaddleHuman();
		void movePaddleAi();
		void movePaddle(Enums::Direction);

	public:
		PlayerPaddle(const std::string& name, float xPosition, float yPosition, bool isAi, Color color);

		void startGame();

		void update();
		void draw() const;

		Rectangle getPaddleRectangle() const;

		void incrementAiPaddleSpeed(int amount);
		
		Vector2 getPosition() const;
		void resetPosition();

		Vector2 getVelocity() const;
	};
}
