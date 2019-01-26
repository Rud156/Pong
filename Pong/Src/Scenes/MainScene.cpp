#include "MainScene.h"
#include "../Utils/ExtensionFunctions.h"

namespace Scenes
{
	MainScene* MainScene::_instance = nullptr;

	MainScene::MainScene()
	{
		// Constructor must be empty and not call any reference
		// Or a recursive stackoverflow exception will occur
	}

	MainScene* MainScene::Instance()
	{
		if (_instance == nullptr)
			_instance = new MainScene();

		return _instance;
	}

	MainScene::~MainScene()
	{
		clearMemory();
	}

	void MainScene::clearMemory()
	{
		delete Instance()->_humanPlayer;
		delete Instance()->_aiPlayer;
		delete Instance()->_ball;
	}

	bool MainScene::countdownToGameStart()
	{
		if (Instance()->_current_countdown <= 0)
			return true;

		const auto displayTime = Utils::ExtensionFunctions::
			FormatFloatToStringInt(Instance()->_current_countdown + 1);

		const char* displayText;
		if (Instance()->_current_level <= 1)
			displayText = Instance()->_first_play;
		else
			displayText = Instance()->_subsequent_play;

		const auto screenWidthMiddle = Instance()->_screen_width / 2;
		const auto screenHeightMiddle = Instance()->_screen_height / 2;

		const auto displayTextWidth = MeasureText(displayText, 25);
		DrawText(displayText, screenWidthMiddle - displayTextWidth / 2,
		         screenHeightMiddle - 50, 25, RED);

		const auto displayTimeCString = displayTime.c_str();
		const auto displayTimeWidth = MeasureText(displayTimeCString, 30);
		DrawText(displayTimeCString, screenWidthMiddle - displayTimeWidth / 2,
		         screenHeightMiddle + 50, 30, BLUE);

		Instance()->_current_countdown -= GetFrameTime();

		return Instance()->_current_countdown <= 0;
	}

	void MainScene::updateBall()
	{
	}

	void MainScene::updatePlayers()
	{
	}

	void MainScene::checkPaddleAndBallCollision()
	{
	}

	void MainScene::setupOrResetScene()
	{
	}

	bool MainScene::update()
	{
		updateBall();
		updatePlayers();

		const auto countdownComplete = Instance()->countdownToGameStart();
		if (!countdownComplete)
			return false;

		return false;
	}
}
