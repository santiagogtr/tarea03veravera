#pragma once
#include "Ship.h"
class EnemyShip : public Ship
{
private:
	float _elapsed;
	int color;
public:
	EnemyShip(float agent_width, float agent_height, glm::vec2 position,std::string texture, int color);
	void update(float deltaTime);
	bool outside();
	bool colision(int comprobarX, int comprobsrY);
	int getColor();
	~EnemyShip();
};

