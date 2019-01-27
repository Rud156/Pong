#include "Flasher.h"
#include "../Utils/ExtensionFunctions.h"

namespace Common
{
	Vector2 Flasher::shakerUpdate()
	{
		if (!this->_start_shaking)
			return this->_position;

		const auto x = this->_position.x +
			Utils::ExtensionFunctions::Map(Utils::ExtensionFunctions::GetRandom01(),
			                               0, 1,
			                               -this->_shake_amount, this->_shake_amount);
		const auto y = this->_position.y +
			Utils::ExtensionFunctions::Map(Utils::ExtensionFunctions::GetRandom01(),
			                               0, 1,
			                               -this->_shake_amount, this->_shake_amount);

		this->_current_duration -= GetFrameTime();
		if (this->_current_duration <= 0)
			this->stopShake();

		return {x, y};
	}

	void Flasher::startShake()
	{
		if (this->_start_shaking)
			this->_current_duration += this->_shake_duration;
		else
		{
			this->_start_shaking = true;
			this->_current_duration = this->_shake_duration;
		}
	}

	void Flasher::stopShake()
	{
		this->_start_shaking = false;
	}
}
