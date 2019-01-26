#pragma once

#include "raylib.h"

namespace Player
{
	class PlayerPaddle
	{
	private:
		Vector2 _position;
		Color _color;

		const int _movement_speed = 5;
		bool is_ai;

		void movePaddleHuman();
		void movePaddleAi();

	public:

	};
}
