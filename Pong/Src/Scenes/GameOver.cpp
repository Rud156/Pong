#include "GameOver.h"
#include <string>
#include "../Utils/ExtensionFunctions.h"

namespace Scenes
{
	GameOver* GameOver::_instance = nullptr;

	GameOver::GameOver()
	{
		// Constructor must be empty and not call any reference
		// Or a recursive stackoverflow exception will occur
	}

	GameOver* GameOver::Instance()
	{
		if (_instance == nullptr)
			_instance = new GameOver();

		return _instance;
	}

	void GameOver::setupScene()
	{
		Instance()->_screen_width = GetScreenWidth();
		Instance()->_screen_height = GetScreenHeight();
	}

	bool GameOver::updateScene()
	{
		const auto screenWidthMiddle = Instance()->_screen_width / 2;
		const auto screenHeightMiddle = Instance()->_screen_height / 2;

		const auto survivedTextWidth = MeasureText(Instance()->_survived_text, 30);
		DrawText(Instance()->_survived_text, screenWidthMiddle - survivedTextWidth / 2,
		         screenHeightMiddle - 100, 30, GREEN);

		const auto levelNumberWidth = MeasureText(Instance()->_level_text.c_str(), 25);
		DrawText(Instance()->_level_text.c_str(), screenWidthMiddle - levelNumberWidth / 2,
		         screenHeightMiddle - 50, 25, GREEN);

		const auto mousePosition = GetMousePosition();
		const auto buttonWidth = 200.0f;
		const auto buttonHeight = 50.0f;
		const Rectangle buttonBounds = {
			static_cast<float>(screenWidthMiddle) - buttonWidth / 2, screenHeightMiddle + 100,
			buttonWidth, buttonHeight
		};

		DrawRectangleLinesEx(buttonBounds, 3, Instance()->_button_color);

		const auto replayWidth = MeasureText(Instance()->_replay_text, 25);
		DrawText(Instance()->_replay_text, buttonBounds.x + buttonWidth / 2 - replayWidth / 2.0f,
		         buttonBounds.y + buttonHeight / 2 - 25 / 2.0f,
		         25, Instance()->_button_color);

		if (CheckCollisionPointRec(mousePosition, buttonBounds))
		{
			Instance()->_button_color = MAGENTA;

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				return true;
		}
		else
			Instance()->_button_color = ORANGE;

		return false;
	}

	void GameOver::setLevelCount(const int levelCount)
	{
		Instance()->_level_count = levelCount;
		Instance()->_level_text = Utils::ExtensionFunctions::FormatFloatToStringInt(levelCount).c_str();
	}
}
