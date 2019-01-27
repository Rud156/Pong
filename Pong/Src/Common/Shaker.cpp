#include "Shaker.h"

namespace Common
{
	void Shaker::startShake()
	{
		this->_start_shaking = true;
		this->_current_duration = this->_shake_duration;
	}

	void Shaker::disableShake()
	{
		this->_start_shaking = false;
	}
}
