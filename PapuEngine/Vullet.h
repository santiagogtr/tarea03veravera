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
public:
	void draw(SpriteBacth& spritebatch);
	Vullet(std::string texture,glm::vec2 position);
	~Vullet();
};

