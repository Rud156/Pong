#include "raylib.h"
#include "ExtensionFunctions.h"

namespace Utils
{
	float ExtensionFunctions::Map(const float from, const float fromMin, const float fromMax, const float toMin,
	                              const float toMax)
	{
		const auto fromAbs = from - fromMin;
		const auto fromMaxAbs = fromMax - fromMin;

		const auto normal = fromAbs / fromMaxAbs;

		const auto toMaxAbs = toMax - toMin;
		const auto toAbs = toMaxAbs * normal;

		const auto to = toAbs + toMin;

		return to;
	}

	float ExtensionFunctions::Lerp(const float start, const float stop, const float amount)
	{
		return amount * (stop - start) + start;
	}

	float ExtensionFunctions::GetRandom01()
	{
		return  GetRandomValue(0, 1000) / 1000.0;
	}

	std::string ExtensionFunctions::FormatFloatToStringInt(const float number)
	{
		const auto intNumber = static_cast<int>(number);
		return std::to_string(intNumber);
	}
}
