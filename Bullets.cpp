#include "Bullets.h"

Bullets::Bullets(sf::Texture* texture, float pos_X, float pos_Y, float dir_X, float dir_Y, float movement_speed)
{
	this->bullet.setTexture(*texture);
	this->bullet.scale(1.f, 1.f);

	this->bullet.setPosition(pos_X, pos_Y);
	this->direction.x = dir_X;
	this->direction.y = dir_Y;
	this->movementSpeed = movement_speed;

}

Bullets::~Bullets()
{

}

void Bullets::update()
{
	//movement update
	this->bullet.move(this->movementSpeed * this->direction);

}

void Bullets::render(sf::RenderTarget* target)
{
	target->draw(this->bullet);
 }

const sf::FloatRect Bullets::getBounds() const
{
	return this->bullet.getGlobalBounds();
}


