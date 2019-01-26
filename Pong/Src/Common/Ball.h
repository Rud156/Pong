#pragma once

#include "raylib.h"

namespace Common
{
	class Ball
	{
	private:
		int _window_width;
		int _window_height;

		const int _max_ball_speed = 100;
		const int _min_ball_speed = 10;
		float _ball_speed;

		Vector2 _spawn_position{};
		Vector2 _position{};
		Vector2 _velocity{};

		bool _ball_launched{};

		const int _radius = 10;
		Color _color{};

		void checkAndLimitBallVelocity();
		void checkCollisionWithPaddle(Rectangle rectangle, Vector2 paddleVelocity);

	public:
		Ball(float xPosition, float yPosition, Color color);
		void draw() const;
		void update();

		void launchBall(Vector2 playerVelocity);
		void incrementBallSpeed(float amount);

		Vector2 getPosition() const;
		void setPosition(Vector2 position);
		void resetPosition();

		bool isBallOutOfScreen() const;
	};
}
