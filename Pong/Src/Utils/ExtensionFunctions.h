#pragma once

#include <string>

namespace Utils
{
	class ExtensionFunctions
	{
	public:
		static float Map(float from, float fromMin, float fromMax, float toMin, float toMax);
		static float Lerp(float start, float stop, float amount);

		static float GetRandom01();

		static std::string FormatFloatToStringInt(float number);
	};
}
