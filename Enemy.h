//define once!
#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib>
#include<time.h>

class Enemy
{
private:
	float pointCount;
	sf::CircleShape shape;
	float hp;
	float hpMax;
	int damage, points;
	int type;
	float speed,hpPercent;

	void initVariables();
	void initShape();

public:
	//Enemy();
	Enemy(float posX, float posY);
	virtual ~Enemy();

	//getting position of enemy in the screen
	sf::FloatRect getBounds();

	//returning points
	const int& getPoints() const;
	const int& getDamage() const;
	
	const float& getHp() const;
	void loseHP(const int value);

	void setColor();

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

