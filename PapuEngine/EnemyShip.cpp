#include "EnemyShip.h"



EnemyShip::EnemyShip(float agent_width, float agent_height, glm::vec2 position, std::string texture, int color)
	:Ship(agent_width,agent_height,position,texture),_elapsed(0)
{
	this->color = color;
}

void EnemyShip::update(float deltaTime) {
	_elapsed += deltaTime;
	_position.y -= 5;
}

bool EnemyShip::outside() {
	if (_position.y < 20) return true;
	return false;
}


bool EnemyShip::colision(int comprobarX, int comprobsrY) {
	if (comprobarX + 40 >= _position.x && comprobarX <=_position.x && comprobsrY >= _position.y && comprobsrY-20 <= _position.y)
		return true;
	else
		return false;

}

int EnemyShip::getColor() {
	return color;

}

EnemyShip::~EnemyShip()
{
}
