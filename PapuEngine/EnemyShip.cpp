#include "EnemyShip.h"



EnemyShip::EnemyShip(float agent_width, float agent_height, glm::vec2 position, std::string texture)
	:Ship(agent_width,agent_height,position,texture),_elapsed(0)
{
	
}

void EnemyShip::update(float deltaTime) {
	_elapsed += deltaTime;
	_position.y -= 5;
}


EnemyShip::~EnemyShip()
{
}
