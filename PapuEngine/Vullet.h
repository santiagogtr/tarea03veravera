#pragma once
#include <string>
#include <glm\glm.hpp>
#include "SpriteBacth.h"

class Vullet
{
private:
	std::string _texture;
	int _textureID;
	float _elapsed;
	float distance = 100;
	float initDistance;
	bool facing;
public:
	void draw(SpriteBacth& spritebatch);
	glm::vec2 _position;
	Vullet(std::string texture,glm::vec2 position, bool facinW);
	bool update(float deltaTime,int pantallaD, int pantallaI);
		bool outside();
	~Vullet();
};

