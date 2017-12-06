#include "EnemyShip.h"



EnemyShip::EnemyShip(float agent_width, float agent_height, glm::vec2 position, std::string texture, int color)
	:Ship(agent_width,agent_height,position,texture),_elapsed(0)
{
	this->color = color;
	facing = false;
}

bool EnemyShip::update(float deltaTime, Ship* _ship) {
	_elapsed += deltaTime;
	if ( frecuenciaBala <= 0) {
		frecuenciaBala = 50;
		return true;
	}
	else {
		frecuenciaBala--;
	}
	return false;
}

bool EnemyShip::outside() {
	if (_position.y < 20) return true;
	return false;
}



int EnemyShip::getColor() {
	return color;

}

EnemyShip::~EnemyShip()
{
}
