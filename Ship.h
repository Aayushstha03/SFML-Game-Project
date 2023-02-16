#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>

class Ship
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	//private methods
	void initVariables();
	void initTexture();
	void initSprite();

	//variable for movement
	float moveSpeed;

	float attackCoolDown;
	float attackCoolDownMax;

	int hp, hpMax;


public:
	Ship();
	virtual ~Ship();

	//movement function
	void Move(const float dirX, const float dirY);

	//accessor for player positions
	const sf::Vector2f& getPos() const;
	sf::FloatRect getBounds() const;

	//accessors for player HP
	const int& getHp() const;
	const int& getHpMax() const;

	//functions of the player/ship
	void setPosition(float x, float y);
	void setMoveSpeed(float value);

	void setHP(const int hp);
	void loseHp(const int value);


	void updateCooldown();
	const bool canAttack();


	void update();
	void render(sf::RenderTarget& target);
};

