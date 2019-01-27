// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "raylib.h"
#include "Src/Scenes/MainScene.h"
#include "Src/Scenes/HomeScreen.h"
#include "Src/Scenes/GameOver.h"

int main()
{
	const auto screenWidth = 800;
	const auto screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Pong");
	InitAudioDevice();

	const auto backgroundMusic = LoadSound("resources/audio/background.wav");

	Scenes::HomeScreen::Instance(); // Create Instance of Home Screen
	Scenes::MainScene::Instance(); // Create Instance of Main Screen
	Scenes::GameOver::Instance(); // Create Instance of GameOver Screen

	Scenes::HomeScreen::setupScene();
	Scenes::MainScene::setupOrResetScene();
	Scenes::GameOver::setupScene();

	auto sceneType = Enums::Scene::Home;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		if (!IsSoundPlaying(backgroundMusic))
			PlaySound(backgroundMusic);

		switch (sceneType)
		{
		case Enums::Home:
			{
				const auto gameStarted = Scenes::HomeScreen::drawAndCheckForGameStart();
				if (gameStarted)
				{
					sceneType = Enums::Scene::Main;
					Scenes::MainScene::setupOrResetScene();
				}
			}
			break;

		case Enums::Main:
			{
				const auto gameOver = Scenes::MainScene::update();
				if (gameOver)
					sceneType = Enums::Scene::GameOver;
			}
			break;

		case Enums::GameOver:
			{
				const auto restartGame = Scenes::GameOver::updateScene();
				if (restartGame)
					sceneType = Enums::Scene::Home;
			}
			break;

		default:
			break;
		}

		EndDrawing();
	}

	UnloadSound(backgroundMusic);

	CloseAudioDevice();
	CloseWindow();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
