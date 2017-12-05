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
	}
	if (_inputManager->isKeyDown(SDLK_d)) {
		_position.x += 3.0f;
	}
	if (_inputManager->isKeyDown(SDLK_w)) {
		jumping = true;
	}
	if (_inputManager->isKeyDown(SDLK_s)) {
		_position.y -= 4.0f;
	}
	jump();
}


Ship::~Ship()
{
}
