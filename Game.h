#pragma once
#include <map>
#include<string>
#include<sstream>
#include<ctime>
#include<fstream>

//entity files
#include "Ship.h"
#include "Bullets.h"
#include "Enemy.h"
#include "Shield.h"



class Game 
{
private:
	//window
	sf::RenderWindow* window;
	
	//resources
	
	//using map: which is structure thingy that maps two things
	std::map<std::string, sf::Texture*> textures;

	//main player
	Ship* ship;
	float hpPercent;

	//bullet objects
	std::vector<Bullets*> bulletNum;

	//background stuff
	sf::Sprite worldBackground;
	sf::Texture worldBackgroundtexture;

	//pause game?
	bool pause;

	//HUD
	sf::Font font;
	sf::Text pointsText;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBG;

	//previous highscore storage
	int prevScore;
	sf::Text highscoreText;
	bool newHS;

	//object for shield
	Shield sh;
	sf::RectangleShape shield;
	float shieldHpPercent;

	//Tutorial/ Welcome
	bool welcome;
	sf::Sprite welcomeBackground;
	sf::Texture welcomeBackgroundtexture;

	//Gameover screen
	sf::Text gameOverText;

	//points system
	float points;

	//difficulty scaling
	float spawnRate;
	float spawnRateCounter;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemyNum;

	//timer attributes
	sf::Clock clock;
	sf::Time timeElapsed;


	//private methods
	void initializeWindow();
	void initTextures();
	
	//welcome screen init
	void initWelcomeScreen();

	//elements of the game
	void initPlayer();
	void initEnemies();
	void initHUD();
	void initSystem();

	void resetGame();

public:
	Game();
	virtual ~Game();

	//game functions
	void run();

	void updatePollEvents();
	void updateInputs();
	void updateHUD();
	void updateWorld();
	void updateCollisions();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateHighscore();
	void update();

	//welcome screen render!
	void renderWelcomeScreen();

	//game elements render
	void renderHUD();
	void renderBackground();
	void render();

};