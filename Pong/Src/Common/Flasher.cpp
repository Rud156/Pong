#include "Flasher.h"

namespace Common
{
	void Flasher::startFlash()
	{
		if (!this->_start_flash)
		{
			this->_current_flash_count = this->_flash_count;
			this->_flash_on = false;
			this->_current_flash_time = this->_flash_time;
			this->_start_flash = true;
		}
	}

	void Flasher::flashScreenUpdate()
	{
		if (!this->_start_flash)
			return;

		ClearBackground(this->_screen_color);

		if (this->_current_flash_time <= 0)
		{
			if (this->_current_flash_count <= 0)
			{
				this->_start_flash = false;
				return;
			}

			if (!this->_flash_on)
				this->_screen_color = RED;
			else
			{
				this->_screen_color = BLACK;
				this->_current_flash_count -= 1;
			}

			this->_flash_on = !this->_flash_on;
			this->_current_flash_time = this->_flash_time;
		}

		this->_current_flash_time -= GetFrameTime();
	}
}
