#include "Enemy.h"
#include<iostream>

void Enemy::initVariables()
{
	this->pointCount = rand() % 12 + 6; //between 6 and 20(12+6)
	this->speed = (9 - static_cast<float>(this->pointCount) / 2.f);
	this->type = 0;
	this->hpMax = (static_cast<int>(this->pointCount) / 4);
	this->hp = this->hpMax;
	this->damage = static_cast<int>(this->pointCount);
	this->points = static_cast<int>(this->pointCount);
}

void Enemy::initShape()
{
	//this function generates the shape/sprite of the enemy!
	this->shape.setRadius(this->pointCount*6);
	this->shape.setPointCount(this->pointCount);
	
	//seperate function to assign color as this is going to be dynamic!
	//HSL hue saturation and lightness color format!
	this->shape.setFillColor(sf::Color(255, 38, 59));
	this->shape.setOutlineColor(sf::Color());
	this->shape.setOutlineThickness(5.f);
}

Enemy::Enemy()
{
}

Enemy::Enemy(float posX, float posY)
{
	//intializing the enemies variabels
	this->initVariables();
	//called after initializing the Enemy's shape,damage and color
	this->initShape();

	this->shape.setPosition(posX, posY);
}

Enemy::~Enemy()
{
}

sf::FloatRect Enemy::getBounds()
{

	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const int& Enemy::getHp() const
{
	return this->hp;
}

void Enemy::loseHP(const int value)
{
	this->hp -= value;

	if (this->hp < 0)
		this->hp = 0;

}

void Enemy::setColor()
{
	if (this->hp/this->hpMax > 0.66f)
		this->shape.setFillColor(sf::Color(255, 38, 59));
	else if(this->hpMax - this->hp > 0.33f)
		this->shape.setFillColor(sf::Color(255, 117, 59));
	else if(this->hpMax - this->hp > 0)
		this->shape.setFillColor(sf::Color(255, 179, 59));
}

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
