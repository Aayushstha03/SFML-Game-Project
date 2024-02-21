#include "Enemy.h"


void Enemy::initVariables()
{
	//random seed using current time
	srand((unsigned)time(NULL));

	this->pointCount = rand() % 12 + 6; //between 6 and 20(12+6)
	this->speed = (10 - static_cast<float>(this->pointCount) / 2.8f);
	//this->type = 0;
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
	//setting origin to centre for rotation
	
	this->shape.setOrigin(this->shape.getLocalBounds().width / 2, this->shape.getLocalBounds().height / 2);

	//seperate function to assign color as this is going to be dynamic!
	//HSL hue saturation and lightness color format!
	this->shape.setFillColor(sf::Color(255, 38, 59));
	this->shape.setOutlineColor(sf::Color());
	this->shape.setOutlineThickness(5.f);
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

const float& Enemy::getHp() const
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
	this->hpPercent = static_cast<float>((this->hp / this->hpMax) * 100);
	//std::cout << this->hpPercent;

	if (this->hpPercent > 75.f)
		this->shape.setFillColor(sf::Color(255, 38, 59));
	else if (this->hpPercent > 50.f)
		this->shape.setFillColor(sf::Color(255, 117, 59));
	else if (this->hpPercent > 25.f)
		this->shape.setFillColor(sf::Color(255, 179, 59));

}

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
	this->shape.rotate(1);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
