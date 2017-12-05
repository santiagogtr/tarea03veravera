#pragma once
#include <string>
#include <glm\glm.hpp>
#include "SpriteBacth.h"

class Vullet
{
private:
	std::string _texture;
	glm::vec2 _position;
	int _textureID;
	float _elapsed;
	float distance = 100;
	float initDistance;
	bool facing;
public:
	void draw(SpriteBacth& spritebatch);
	Vullet(std::string texture,glm::vec2 position, bool facinW);
	bool update(float deltaTime,int pantalla);
		bool outside();
	~Vullet();
};

