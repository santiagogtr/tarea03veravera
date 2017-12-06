#pragma once
#include "SpriteBacth.h"
#include <glm\glm.hpp>
#include "GLTexture.h"
#include <string>
class Background
{
private:
	std::string _texture;
	int _textureID;
public:
	void draw(SpriteBacth& spritebatch,int posicion);
	Background(std::string texture);
	~Background();
};

