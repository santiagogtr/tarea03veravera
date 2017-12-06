#include "EnemyShip.h"



EnemyShip::EnemyShip(float agent_width, float agent_height, glm::vec2 position, std::string texture, int color)
	:Ship(agent_width,agent_height,position,texture),_elapsed(0)
{
	this->color = color;
	facing = false;
}

bool EnemyShip::update(float deltaTime, Ship* _ship) {
	_elapsed += deltaTime;
	if (_ship->getPosition().x > _position.x) {
		facing = true;
	}
	else {
		facing = false;
	}
	switch (color) {
	case 1:
		if (frecuenciaBala <= 0) {
			frecuenciaBala = 80;
			return true;
		}
		else {
			frecuenciaBala--;
		}
		return false;
		break;
	case 2:
		if (facing) {
			_position.x += 2;
		}
		else {
			_position.x -= 2;
		}

		if (_position.x >= _ship->getPosition().x-200 && _position.x <= _ship->getPosition().x+200) {
			_position.y--;
		}

		return false;
	}
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
