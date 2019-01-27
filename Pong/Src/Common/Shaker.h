#pragma once

namespace Common
{
	class Shaker
	{
	protected:
		float _shake_duration;
		float _shake_amount;

		bool _start_shaking;
		float _current_duration;

		virtual void shakerUpdate();
		void startShake();
		void disableShake();
	};
}
