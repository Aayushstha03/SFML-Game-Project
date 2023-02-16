//define once!
#pragma once
#include<SFML/Graphics.hpp>

class Enemy
{
private:
	float pointCount;
	sf::CircleShape shape;
	int hp, hpMax, damage, points;
	int type;
	float speed;

	void initVariables();
	void initShape();

public:
	Enemy();
	Enemy(float posX, float posY);
	virtual ~Enemy();

	//getting position of enemy in the screen
	sf::FloatRect getBounds();

	//returning points
	const int& getPoints() const;
	const int& getDamage() const;
	
	const int& getHp() const;
	void loseHP(const int value);

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

