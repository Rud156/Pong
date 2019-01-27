#include "Ball.h"
#include "../Utils/ExtensionFunctions.h"
#include "../Utils/VectorHelpers.h"
#include <cmath>

namespace Common
{
	Ball::Ball(float xPosition, float yPosition, const Color color)
	{
		this->_window_width = GetScreenWidth();
		this->_window_height = GetScreenHeight();

		this->_spawn_position = {xPosition, yPosition};
		this->_position = {xPosition, yPosition};
		this->_velocity = {0, 0};

		this->_color = color;
		this->_ball_speed = this->_min_ball_speed;
	}

	void Ball::checkAndLimitBallVelocity()
	{
		const auto y = this->_velocity.y;
		const auto x = this->_velocity.x;

		const auto yAbs = abs(y);
		const auto direction = y < 0 ? -1 : 1;

		float normalizedVelocity;

		if (yAbs > this->_max_ball_speed)
			normalizedVelocity = this->_max_ball_speed;
		else if (yAbs < this->_min_ball_speed)
			normalizedVelocity = this->_min_ball_speed;
		else
			normalizedVelocity = this->_ball_speed;

		this->_velocity = {x, normalizedVelocity * direction};
	}

	void Ball::checkCollisionWithPaddle(const Rectangle rectangle, const Vector2 paddleVelocity)
	{
		const auto ballCollided = CheckCollisionCircleRec(this->_position, this->_radius, rectangle);

		if (ballCollided)
		{
			const auto xVelocity = paddleVelocity.x - this->_velocity.x;
			const auto yVelocity = -this->_velocity.y;

			this->_velocity = {xVelocity, yVelocity};
		}
	}

	void Ball::draw() const
	{
		const auto x = this->_position.x;
		const auto y = this->_position.y;

		DrawCircle(x, y, this->_radius, this->_color);
	}

	void Ball::update()
	{
		if (!this->_ball_launched)
			return;

		const auto x = this->_position.x;
		if (x < -this->_radius || x > this->_window_width + this->_radius)
			this->_velocity = {-this->_velocity.x, this->_velocity.y};

		this->checkAndLimitBallVelocity();
		this->_position = Utils::VectorHelpers::Add(this->_position,
		                                            Utils::VectorHelpers::Mult(this->_velocity, GetFrameTime()));
	}

	void Ball::launchBall(Vector2 playerVelocity)
	{
		this->_ball_launched = true;
		const auto launchVelocity = Utils::ExtensionFunctions::GetRandom01() * this->_ball_speed +
			this->_min_ball_speed;

		this->_velocity = {playerVelocity.x, -launchVelocity};
	}

	void Ball::incrementBallSpeed(const float amount)
	{
		if (this->_ball_speed + amount > this->_max_ball_speed)
			this->_ball_speed = this->_max_ball_speed;
		else
			this->_ball_speed = this->_ball_speed + amount;
	}

	Vector2 Ball::getPosition() const
	{
		return this->_position;
	}

	void Ball::setPosition(const Vector2 position)
	{
		if (this->_ball_launched)
			return;

		this->_position = position;
	}

	void Ball::resetPosition()
	{
		this->_position = this->_spawn_position;
	}

	bool Ball::isBallOutOfScreen() const
	{
		const auto y = this->_position.y;
		return y < -this->_radius || y > this->_window_height + this->_radius;
	}
}
