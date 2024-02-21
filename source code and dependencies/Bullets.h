#pragma once
#include<SFML/Graphics.hpp>

class Bullets
{

private:
	sf::Sprite bullet;
	
	//sf::Texture* texture;
	float movementSpeed;
	sf::Vector2f direction;

public:
	//def cons
	Bullets();
	
	Bullets(sf::Texture* texture, float pos_X, float pos_Y, float dir_X, float dir_Y, float movement_speed);
	
	virtual ~Bullets();

	//accesor
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

