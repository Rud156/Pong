#include "MainScene.h"
#include "../Utils/ExtensionFunctions.h"
#include <iostream>

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
		if (!Instance()->_game_started)
		{
			auto humanPosition = Instance()->_humanPlayer->getPosition();
			humanPosition.y -= 15;

			Instance()->_ball->setPosition(humanPosition);
		}

		Instance()->_ball->draw();
		Instance()->_ball->update();

		checkPaddleAndBallCollision();

		if (Instance()->_ball->isBallOutOfScreen())
			changeLevel();
	}

	void MainScene::createBall()
	{
		Instance()->_ball = new Common::Ball(
			Instance()->_screen_width / 2.0f,
			Instance()->_screen_height - 35,
			ORANGE
		);
	}

	void MainScene::updatePlayers()
	{
		Instance()->_humanPlayer->draw();
		Instance()->_humanPlayer->update();

		Instance()->_aiPlayer->draw();
		Instance()->_aiPlayer->update();
	}

	void MainScene::checkPaddleAndBallCollision()
	{
		const auto humanRectangle = Instance()->_humanPlayer->getPaddleRectangle();
		const auto aiRectangle = Instance()->_aiPlayer->getPaddleRectangle();

		const auto humanVelocity = Instance()->_humanPlayer->getVelocity();
		const auto aiVelocity = Instance()->_aiPlayer->getVelocity();

		Instance()->_ball->checkCollisionWithPaddle(humanRectangle, humanVelocity);
		Instance()->_ball->checkCollisionWithPaddle(aiRectangle, aiVelocity);
	}

	void MainScene::changeLevel()
	{
		const auto ballPosition = Instance()->_ball->getPosition();
		if (ballPosition.y < 0)
			Instance()->_human_player_score += 1;
		else
			Instance()->_ai_player_score += 1;

		Instance()->_game_started = false;

		delete Instance()->_ball;
		createBall();
		Instance()->_aiPlayer->setBall(Instance()->_ball);

		Instance()->_current_countdown = Instance()->_max_countdown;
	}

	void MainScene::setupOrResetScene()
	{
		Instance()->clearMemory();

		Instance()->_screen_width = GetScreenWidth();
		Instance()->_screen_height = GetScreenHeight();

		Instance()->_current_countdown = Instance()->_max_countdown;
		Instance()->_game_started = false;
		Instance()->_current_level = 0;

		createBall();

		Instance()->_humanPlayer = new Player::PlayerPaddle(
			"Human",
			Instance()->_screen_width / 2.0f,
			Instance()->_screen_height - 20,
			false,
			PURPLE
		);
		Instance()->_aiPlayer = new Player::PlayerPaddle(
			"Computer",
			Instance()->_screen_width / 2.0f,
			0,
			true,
			BLUE,
			Instance()->_ball
		);
	}

	bool MainScene::update()
	{
		updateBall();
		updatePlayers();

		const auto countdownComplete = Instance()->countdownToGameStart();
		if (!countdownComplete)
			return false;

		if (IsKeyPressed(KEY_SPACE) && !Instance()->_game_started)
		{
			Instance()->_ball->launchBall(Instance()->_humanPlayer->getVelocity());
			Instance()->_game_started = true;

			Instance()->_aiPlayer->startGame();
			Instance()->_humanPlayer->startGame();
		}

		return false;
	}
}
