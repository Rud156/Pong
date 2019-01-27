#pragma once

#include "raylib.h"
#include <vector>

namespace Common
{
	class Ball
	{
	private:
		int _window_width;
		int _window_height;

		const int _ball_speed_increment_amount = 50;
		const int _max_ball_speed = 700;
		const int _min_ball_speed = 300;
		float _ball_speed;

		Vector2 _spawn_position{};
		Vector2 _position{};
		Vector2 _velocity{};

		Sound _explode_sound{};
		Sound _ball_launch_sound{};
		bool _ball_launched{};

		const int _radius = 10;
		Color _color{};

		int _max_history;
		std::vector<Vector2> _history;

		void checkAndLimitBallVelocity();
		void checkBallScreenEdgePosition();

		void setHistory();
		void drawTrails();

	public:
		Ball(float xPosition, float yPosition, Color color);
		~Ball();

		void draw();
		void update();
		void checkCollisionWithPaddle(Rectangle rectangle, Vector2 paddleVelocity);

		void launchBall(Vector2 playerVelocity);
		void incrementBallSpeed();

		Vector2 getPosition() const;
		void setPosition(Vector2 position);
		void resetBallStats();

		bool isBallOutOfScreen() const;
	};
}
