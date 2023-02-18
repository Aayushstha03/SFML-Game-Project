#include "Ship.h"
#
Ship::Ship()
{
	//initialize all the variables
	this->initVariables();
	//loading the ships asssets
	this->initTexture();
	this->initSprite();
}

Ship::~Ship()
{

}

void Ship::Move(const float dirX, const float dirY)
{
	this->sprite.move(this->moveSpeed * dirX, this->moveSpeed * dirY);
}

const sf::Vector2f& Ship::getPos() const
{
	return this->sprite.getPosition();
}

sf::FloatRect Ship::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Ship::getHp() const
{
	return this->hp;
}

const int& Ship::getHpMax() const
{
	return this->hpMax;
}

void Ship::initTexture()
{
	//load texture from file
	if (!this->texture.loadFromFile("Textures/Ship2.png"))
		std::cout << "ERROR:SHIP CLASS:Texture not found!"<<std::endl;
}


void Ship::initSprite()
{
	//set the texture as sprite
	this->sprite.setTexture(this->texture);

	//resizing the sprite
	//scale by factors in X and Y axis
	this->sprite.scale(1.f, 1.f);
}

//for intializing all the variables that we require
void Ship::initVariables()
{
	//HP 
	this->hpMax = 200;
	this->hp = this->hpMax;
	
	//movement speed
	this->moveSpeed = 15.f;
	this->attackCoolDownMax = 10.f;
	this->attackCoolDown = this->attackCoolDownMax;
}

void Ship::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Ship::setMoveSpeed(float value)
{
	this->moveSpeed = value;
}

void Ship::setHP(const int hp)
{
	this->hp = hp;
}

void Ship::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Ship::updateCooldown()
{
	if (this->attackCoolDown < this->attackCoolDownMax)
		this->attackCoolDown += 1.55f;
}

const bool Ship::canAttack()
{
	if (this->attackCoolDown >= this->attackCoolDownMax)
	{
		this->attackCoolDown = 0;
		return true;
	}
	else
		return false;
}

void Ship::update()
{
	this->updateCooldown();
}

void Ship::render(sf::RenderTarget& target)
{
	//rendering the ship
	target.draw(this->sprite);
}
