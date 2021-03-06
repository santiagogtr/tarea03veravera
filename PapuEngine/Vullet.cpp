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
	if (facing) {
		glm::vec4 destRect(_position.x + 50, _position.y + 35, -25, 15);
		spritebatch.draw(destRect, uvRect, _textureID, 0.0f, color);
	}
	else {
		glm::vec4 destRect(_position.x - 70, _position.y + 35, 25, 15);
		spritebatch.draw(destRect, uvRect, _textureID, 0.0f, color);
	}
}

bool Vullet::update(float deltaTime, int pantallaD, int pantallaI) {
	_elapsed += deltaTime;
	if (_position.x >= pantallaD || _position.x <= pantallaI)
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
