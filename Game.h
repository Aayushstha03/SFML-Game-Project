#pragma once
#include <map>
#include<string>
#include<sstream>
#include<ctime>
#include<fstream>
#include<SFML/Audio.hpp>

//entity files
#include "Ship.h"
#include "Bullets.h"
#include "Enemy.h"
#include "Shield.h"

class Game 
{
private:
	
	//system attributes
	sf::RenderWindow* window;						//window
	bool pause;
	sf::Font font;									//fonts for UI
	//resources attributes
	std::map<std::string, sf::Texture*> textures;	//using map: which is structure thingy that maps two things

	sf::Sprite worldBackground;						//background sprite and texture
	sf::Texture worldBackgroundtexture;
	
	sf::SoundBuffer shootBuffer;
	sf::Sound shoot;
	sf::SoundBuffer gameAudioBuffer;
	sf::Sound gameAudio;
	sf::SoundBuffer hitBuffer;
	sf::Sound hit;
	bool gameoverSound;
	sf::SoundBuffer gameOverBuffer;
	sf::Sound gameOverSound;
	sf::SoundBuffer shieldHitBuffer;
	sf::Sound shieldHit;

	bool welcome;
	sf::Sprite welcomeBackground;
	sf::Texture welcomeBackgroundtexture;

	//Gameover screen
	sf::Text gameOverText;
	
	//player realted attributes
	Ship* ship;										//main player	
	float hpPercent;								//player hp
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBG;

	//Bullets attributes
	std::vector<Bullets*> bulletNum;				//bullet objects
	
	//Shield related attributes
	Shield sh;										//shield
	sf::RectangleShape shield;
	float shieldHpPercent;

	//Enemies
	std::vector<Enemy*> enemyNum;
	//difficulty scaling for enemies
	float spawnTimer;								//Enemy attributes all
	float spawnTimerMax;
	float spawnRate;
	float spawnRateCounter;
		
	//Points/score related attributes
	float points;
	sf::Text pointsText;							

	//Highscore realted attributes
	int prevScore;
	sf::Text highscoreText;
	bool newHS;
	
	
	//timer attributes
	sf::Clock clock;
	sf::Time timeElapsed;


	//private methods
	void initializeWindow();
	void initTextures();
	void initAudio();
	//welcome screen init
	void initWelcomeScreen();

	//elements of the game
	void initPlayer();
	void initEnemies();
	void initHUD();
	void initSystem();

	//game reset function
	void resetGame();

public:
	Game();
	virtual ~Game();

	//game functions
	void run();

	//update functions
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