#pragma once

#include "raylib.h"

namespace Common
{
	class Flasher
	{
	private:
		const int _flash_count = 3;
		const float _flash_time = 0.1f;

		float _current_flash_time = _flash_time;
		int _current_flash_count = _flash_count;

		bool _flash_on = false;
		bool _start_flash = false;

		Color _screen_color{};

	protected:
		void flashScreenUpdate();
		void startFlash();
	};
}
