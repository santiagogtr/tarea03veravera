#pragma once
#include "Ship.h"
#include "Vullet.h"
#include <vector>

class EnemyShip : public Ship
{
private:
	float _elapsed;
	int color;
public:
	EnemyShip(float agent_width, float agent_height, glm::vec2 position,std::string texture, int color);
	bool update(float deltaTime, Ship* _ship);
	bool outside();
	int frecuenciaBala = 20;
	int getColor();
	~EnemyShip();
};

