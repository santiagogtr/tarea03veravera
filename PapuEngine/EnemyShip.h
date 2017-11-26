#pragma once
#include "Ship.h"
class EnemyShip : public Ship
{
private:
	float _elapsed;
public:
	EnemyShip(float agent_width, float agent_height, glm::vec2 position,std::string texture);
	void update(float deltaTime);
	~EnemyShip();
};

