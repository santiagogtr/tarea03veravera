#include "Vullet.h"
#include "ResourceManager.h"

Vullet::Vullet(std::string texture, glm::vec2 position,bool facinW)
				:_texture(texture),_position(position)
{
	_textureID = ResourceManager::getTexture(_texture).id;
	initDistance = position.x;
	facing = facinW;
}

void Vullet::draw(SpriteBacth& spritebatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA  color;
	color.set(255, 255, 0, 255);
	glm::vec4 destRect(_position.x, _position.y, 20, 35);
	spritebatch.draw(destRect, uvRect, _textureID, 0.0f, color);
}

bool Vullet::update(float deltaTime, int pantalla) {
	_elapsed += deltaTime;
	if (_position.x >= pantalla || _position.x <=0)
		return true;
	if(facing)
	_position.x += 8;
	else
		_position.x -= 8;
	return false;
}

bool Vullet::outside() {
	if (_position.y > 800)return true;
	return false;
}




Vullet::~Vullet()
{
}
