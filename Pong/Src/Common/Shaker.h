#pragma once
#include "raylib.h"

namespace Common
{
	class Flasher
	{
	private:
		const float _shake_duration = 0.5f;
		const float _shake_amount = 20;

		bool _start_shaking;
		float _current_duration;

	protected:
		Vector2 _position;

		void startShake();
		Vector2 shakerUpdate();
		void stopShake();
	};
}
