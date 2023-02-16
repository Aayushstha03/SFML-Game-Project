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
	this->shape.setRadius(this->pointCount*6);
	this->shape.setPointCount(this->pointCount);
	//HSL hue saturation and lightness color format!
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy()
{
}

Enemy::Enemy(float posX, float posY)
{
	this->initVariables();
	//called after initializing the pointCounts and stuff
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

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
