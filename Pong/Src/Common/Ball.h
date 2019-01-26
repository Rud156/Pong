#pragma once

#include "raylib.h"

namespace Common
{
	class Ball
	{
	private:
		const int _max_ball_speed = 100;
		const int _min_ball_speed = 10;

		Vector2 _position;
		const int _radius = 10;

		Color _color;

	public:
		Ball(float xPosition, float yPosition, Color color);
		void draw();
		void update();

		Vector2 getPosition();
	};
}
