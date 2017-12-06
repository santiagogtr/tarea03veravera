#include "Ship.h"
#include <SDL\SDL.h>
#include <iostream>


Ship::Ship(float agent_width, float agent_height, glm::vec2 position,
			std::string texture):
				Agent(agent_width,agent_height, position,texture)
{
}

Ship::Ship(float agent_width, float agent_height, glm::vec2 position,
	std::string texture, InputManager* inputManager) :
	Agent(agent_width, agent_height, position, texture)
{
	_inputManager = inputManager;
}

void Ship::update(float deltaTime) {
	if (_inputManager->isKeyDown(SDLK_a)) {
		_position.x -= 5.0f;
		facing = false;
		changeDirection(97);
	}
	if (_inputManager->isKeyDown(SDLK_d)) {
		_position.x += 5.0f;
		facing = true;
		changeDirection(100);
	}
	if (_inputManager->isKeyDown(SDLK_SPACE)) {
		jumping = true;
	}
	if (_inputManager->isKeyDown(SDLK_s)) {

	}
	jump();
}


Ship::~Ship()
{
}
