#include "PlayerPaddle.h"
#include "../Utils/VectorHelpers.h"

namespace Player
{
	PlayerPaddle::PlayerPaddle(const std::string& name, float xPosition, float yPosition, const bool isAi,
	                           const Color color)
	{
		this->_window_width = GetScreenWidth();
		this->_window_height = GetScreenHeight();

		this->is_ai = isAi;
		this->_spawn_position = {xPosition, yPosition};
		this->_position = this->_spawn_position;
		this->_velocity = {0, 0};

		this->_player_name = name;
		this->_color = color;
	}

	void PlayerPaddle::movePaddleHuman()
	{
		if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT))
			this->movePaddle(Enums::Direction::None);
		else if (IsKeyDown(KEY_LEFT))
			this->movePaddle(Enums::Direction::Left);
		else if (IsKeyDown(KEY_RIGHT))
			this->movePaddle(Enums::Direction::Right);
	}

	void PlayerPaddle::movePaddleAi()
	{
		Enums::Direction direction;
		const auto ballPosition = this->_ball->getPosition();
		const auto positionDiff = ballPosition.x - this->_position.x;

		if (positionDiff < 0)
			direction = Enums::Direction::Left;
		else if (positionDiff > 0)
			direction = Enums::Direction::Right;
		else
			direction = Enums::Direction::None;

		this->movePaddle(direction);
	}

	void PlayerPaddle::movePaddle(Enums::Direction direction)
	{
		this->_velocity = {static_cast<float>(this->_window_width), 0};

		if (direction == Enums::Direction::Left)
			this->_velocity = Utils::VectorHelpers::SetMag(this->_velocity, -this->_movement_speed);
		else if (direction == Enums::Direction::Right)
			this->_velocity = Utils::VectorHelpers::SetMag(this->_velocity, this->_movement_speed);
		else
			this->_velocity = {0, 0};

		this->_position = Utils::VectorHelpers::Add(this->_position,
		                                            Utils::VectorHelpers::Mult(this->_velocity, GetFrameTime()));
	}

	void PlayerPaddle::update()
	{
		if (!this->_game_started)
			return;

		if (this->is_ai)
			this->movePaddleAi();
		else
			this->movePaddleHuman();
	}

	void PlayerPaddle::draw() const
	{
		const auto x = this->_position.x;
		const auto y = this->_position.y;

		DrawRectangle(x, y, this->_paddle_width, this->_paddle_height, this->_color);
	}

	Rectangle PlayerPaddle::getPaddleRectangle() const
	{
		const auto x = this->_position.x;
		const auto y = this->_position.y;

		const Rectangle rectangle = {x, y, this->_paddle_width, this->_paddle_height};
		return rectangle;
	}

	void PlayerPaddle::startGame()
	{
		this->_game_started = true;
	}

	void PlayerPaddle::incrementAiPaddleSpeed(int amount)
	{
		this->_movement_speed += amount;
	}

	Vector2 PlayerPaddle::getPosition() const
	{
		return this->_position;
	}

	void PlayerPaddle::resetPosition()
	{
		this->_position = this->_spawn_position;
	}

	Vector2 PlayerPaddle::getVelocity() const
	{
		return this->_velocity;
	}
}
