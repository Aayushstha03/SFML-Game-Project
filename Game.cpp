#include "Game.h"

void Game::initializeWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Planet Defence", sf::Style::Fullscreen);
	this->window->setFramerateLimit(61);
	this->window->setVerticalSyncEnabled(true);

	this->worldBackgroundtexture.loadFromFile("Textures/background.png");
	this->worldBackground.setTexture(this->worldBackgroundtexture);

}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/Bullet.png");
}

void Game::initAudio()
{
	if (!this->shootBuffer.loadFromFile("Audio/firing.wav") || !this->gameAudioBuffer.loadFromFile("Audio/music.wav"))
		std::cout << "Cannot load the sounds!\n";
	
	this->shoot.setBuffer(this->shootBuffer);
	this->gameAudio.setBuffer(this->gameAudioBuffer);

	this->shoot.setVolume(8);
	this->gameAudio.setLoop(true);
}

void Game::initWelcomeScreen()
{
	//bool to display this once per runtime
	this->welcome = true;
	this->welcomeBackgroundtexture.loadFromFile("Textures/welcome.png");
	this->welcomeBackground.setTexture(this->welcomeBackgroundtexture);

	this->highscoreText.setFont(this->font);
	this->highscoreText.setFillColor(sf::Color::White);
	this->highscoreText.setCharacterSize(30);
	
	std::stringstream hs;
	hs << "Current highscore : " << this->prevScore;
	this->highscoreText.setString(hs.str());
	this->highscoreText.setPosition(this->window->getSize().x - 575.f,
		5.f);
	
}

void Game::initHUD()
{
	//load fonts
	if (!this->font.loadFromFile("Fonts/retroComputer.ttf"))
	{
		std::cout << "Cant load fonts!";
	}

	//initializing points text
	this->pointsText.setFont(this->font);
	this->pointsText.setCharacterSize(30);
	this->pointsText.setFillColor(sf::Color::White);
	this->pointsText.setPosition(5.f, 5.f);

	//Game over Screen! 
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(70);
	this->gameOverText.setFillColor(sf::Color::White);
	this->gameOverText.setString("	    Game Over   \n'R' - Restart Game");
	this->gameOverText.setPosition
	(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);


	//initializing Player HP data
	this->playerHpBar.setSize(sf::Vector2f(120.f, 15.f));
	this->playerHpBar.setFillColor(sf::Color::Green);
	this->playerHpBar.setPosition(this->ship->getPos().x - this->playerHpBar.getSize().x / 2
		, this->ship->getPos().y + 155.f);

	//copy attributes from HpBar!
	this->playerHpBarBG = this->playerHpBar;
	this->playerHpBarBG.setFillColor(sf::Color::Red);

	//initializing the "planet surface"
	this->shield.setSize(sf::Vector2f(this->window->getSize().x, 60));
	this->shield.setFillColor(sf::Color::Magenta);
	this->shield.setPosition(sf::Vector2f(0.f, this->window->getSize().y - 30.f));
}

void Game::initPlayer()
{
	this->ship = new Ship;
	this->ship->setPosition(this->window->getSize().x / 2 - this->ship->getBounds().width / 2.f, this->window->getSize().y - 50.f);
}

void Game::initEnemies()
{
	this->spawnTimerMax = 40.f;
	this->spawnTimer = this->spawnTimerMax;
	this->spawnRate = 0.6f;
	this->spawnRateCounter = 0.f;
}

void Game::initSystem()
{
	this->pause = false;
	this->points = 0;
	this->newHS = false;

	//reading the previous highscore if any to prevScore var;
	std::ifstream readScore("data.dat", std::ios::in);
	if (!readScore)
		std::cout << "Can not find the data file to update highscore!\n";
	readScore >> this->prevScore;
	readScore.close();

}

void Game::resetGame()
{
	//clearing the old ship
	delete this->ship;
	this->initPlayer();

	//clearing the old enemies
	this->enemyNum.clear();
	this->spawnRate = 0.6f;

	//clearing the old bullets
	this->bulletNum.clear();
	
	//resetting the score
	this->points = 0.f;
	
	//welcome screen
	this->welcome = true;

	//Allow highscore updates after resetting 
	this->newHS = false;
}

Game::Game()//constructor
{
	//load window
	this->initializeWindow();
	//load textures
	this->initTextures();
	//load audio
	this->initAudio();
	//points and such
	this->initSystem();
	//initializing the welcome screen
	this->initWelcomeScreen();
	//load players ship
	this->initPlayer();
	//load enemy abstracts
	this->initEnemies();
	//load the HUD
	this->initHUD();

	//this->gameAudio.play();
}

Game::~Game()
{
	this->updateHighscore();

	//then close the window and the ship 
	delete this->window;
	delete this->ship;

	//delete texture else memory leak
	for (auto& i : this->textures)
	{
		//delete the textures from the container
		delete i.second;
	}

	//delete bullets
	for (auto *i : this->bulletNum)
	{
		delete i;
	}

	//delete Enemies
	for (auto* i : this->enemyNum)
	{
		delete i;
	}
}

//Main Game Loop!!!!
void Game::run()
{
	this->gameAudio.play();
	while (this->window->isOpen())
	{
		//basic window controls
		this->updatePollEvents();

		//time record
		//this->timeElapsed = this->clock.getElapsedTime();

		if (this->welcome == true)
		{
			this->renderWelcomeScreen();
		}
		else
		{	
			if (this->ship->getHp() > 0 && this->sh.getHp() > 0) //update the game only if the player is alive!
				this->update();
			else
				this->updateHighscore(); //updating highscore if its valid!
			this->render();	//render function
		}
	}
}

void Game::updatePollEvents()
{
	sf::Event ev;

	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
			this->window->close();
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Enter)
			this->welcome = false;
		if (ev.Event::KeyPressed && ev.key.code == sf::Keyboard::R)
			this->resetGame();
	}
}

void Game::updateInputs()
{

	//movement using WASD keys and arroy keys as well
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->ship->Move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->ship->Move(0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->ship->Move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->ship->Move(1.f, 0.f);
	

	//shooting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&this->ship->canAttack())
	{
		this->bulletNum.push_back(new Bullets(this->textures["BULLET"], this->ship->getPos().x + this->ship->getBounds().width / 2.4f, this->ship->getPos().y - 20.f, 0.f, -1.f, 20.f));
		this->shoot.play();
	}

	//Movement handicap!
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->ship->setMoveSpeed(3.f);
	}
	else
		this->ship->setMoveSpeed(20.f);


}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bulletNum)
	{
		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//removing if its at top of the screen
			delete this->bulletNum.at(counter);
			this->bulletNum.erase(this->bulletNum.begin() + counter);
			//std::cout << this->bulletNum.size()<<std::endl;
			//check number of bullets
			counter--;
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//spawning the enemies
	this->spawnTimer += this->spawnRate;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemyNum.push_back(new Enemy((rand() % (this->window->getSize().x)), -200.f));
		this->spawnTimer = 0.f;
	}

	unsigned counter = 0;
	for (auto* enemy : this->enemyNum)
	{
		enemy->update();
		
		//removing if it spawns to far out 
		if (enemy->getBounds().left < 0.f || (enemy->getBounds().left + enemy->getBounds().width) > this->window->getSize().x)
		{
			delete this->enemyNum.at(counter);
			this->enemyNum.erase(this->enemyNum.begin() + counter);
			--counter;
		}
		//removing if its at bottom of the screen
		else if (enemy->getBounds().top > window->getSize().y - 60.f)
		{
			//damage the planet/mothership whatever
			this->sh.loseHP(this->enemyNum.at(counter)->getDamage());
			//implement the shield damaging enemy and taking damage as well??

			delete this->enemyNum.at(counter);
			this->enemyNum.erase(this->enemyNum.begin() + counter);
			--counter;
		}
		//removing the enemy and damage dealt if contact!
		else if (enemy->getBounds().intersects(this->ship->getBounds()))
		{
			this->ship->loseHp(this->enemyNum.at(counter)->getDamage());
			delete this->enemyNum.at(counter);
			this->enemyNum.erase(this->enemyNum.begin() + counter);
			--counter;
		}
		++counter;
	}
	
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemyNum.size(); i++)
	{
		bool enemy_deleted = false;
		for (int k = 0; k < this->bulletNum.size() && !enemy_deleted; k++)
		{
			//Bullet and Enemy collision!
			if (this->bulletNum[k]->getBounds().intersects(this->enemyNum[i]->getBounds()))
			{
				//damage dealth per bullet
				this->enemyNum[i]->loseHP(1);
				//resetting color of that enemy after it takes damage
				this->enemyNum[i]->setColor();

				if (this->enemyNum[i]->getHp() == 0)
				{
					//adding points for killed enemies
					this->points += this->enemyNum[i]->getPoints();
					this->spawnRateCounter += this->enemyNum[i]->getPoints();

					if (this->spawnRateCounter >= 100)
					{
						this->spawnRateCounter = 0;
						this->spawnRate += 0.05f;
						//std::cout << spawnRate;
					}

					//deleting enemy
					delete this->enemyNum[i];
					this->enemyNum.erase(this->enemyNum.begin() + i);

					enemy_deleted = true;
					//after deleting a enemy continue loop for another enemy!
				}			

				//deleting bullet
				delete this->bulletNum[k];
				this->bulletNum.erase(this->bulletNum.begin() + k);
			}
		}
	}
}

void Game::updateHUD()
{
	//creating string to print on the window
	std::stringstream ss;
	ss <<"Points : " << this->points;	
	this->pointsText.setString(ss.str());

	//updating player HP bar and such

	//calculating HP percentage
	hpPercent = static_cast<float>(this->ship->getHp()) / this->ship->getHpMax();
	//original size * current hpPercent to generate the length!
	this->playerHpBar.setSize(sf::Vector2f(120.f * hpPercent, this->playerHpBar.getSize().y));

	//moving the hp bar to new position relative to the ship
	this->playerHpBar.setPosition(this->ship->getPos().x
		, this->ship->getPos().y + 155.f);
	this->playerHpBarBG.setPosition(this->ship->getPos().x
		, this->ship->getPos().y + 155.f);

	//for the planet/shield
	//generating fraction of current HP/ Total HP
	shieldHpPercent = (this->sh.getHp() / this->sh.getHpMax()) * 100;
	//std::cout << shieldHpPercent<<"\t";
	//changing color in accordance to HP percentage
	if (shieldHpPercent > 75.f || shieldHpPercent == 1)
		this->shield.setFillColor(sf::Color(105, 0, 248));
	else if (shieldHpPercent >= 50.f)
		this->shield.setFillColor(sf::Color(105, 0, 180));
	else if (shieldHpPercent >= 25.f)
		this->shield.setFillColor(sf::Color(105, 0, 102));
	else if (shieldHpPercent >= 0.f)
		this->shield.setFillColor(sf::Color(105, 0, 66));
}

void Game::updateWorld()
{
}

void Game::updateCollisions()
{
	//left&right or Top&bottom can't happen simultaneously so if and else if!

	//checking collion in left and right
	if (this->ship->getBounds().left < 0.f)
	{
		this->ship->setPosition(0.f, this->ship->getBounds().top);
	}
	//right
	else if (this->ship->getBounds().left + this->ship->getBounds().width  >= this->window->getSize().x)
	{
		this->ship->setPosition(this->window->getSize().x - this->ship->getBounds().width, this->ship->getBounds().top);
	}

	//checking collision in top and bottom
	if (this->ship->getBounds().top < 0.f)
	{
		this->ship->setPosition(this->ship->getBounds().left, 0.f);
	}

	//bottom
	else if (this->ship->getBounds().top + this->ship->getBounds().height >= this->window->getSize().y - 50.f)
	{
		this->ship->setPosition(this->ship->getBounds().left, this->window->getSize().y - this->ship->getBounds().height - 50.f);
	}

}

void Game::updateHighscore()
{
	if (!(this->newHS) && this->points > this->prevScore)
	{
		this->newHS = true;
		this->prevScore = this->points;
		std::stringstream hs;
		hs << "Current highscore : " << this->prevScore;
		this->highscoreText.setString(hs.str());

		std::ofstream writeScore("data.dat", std::ios::out);
		if (!writeScore)
			std::cout << "The data file couldn't be accessed!";
		writeScore << this->prevScore;
		writeScore.close();
	}
}

void Game::update()
{
	this->updateInputs();

	this->ship->update();

	this->updateCollisions();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateHUD();

	this->updateWorld();

}

void Game::renderHUD()
{
	this->window->draw(this->pointsText);
	this->window->draw(this->playerHpBarBG);
	this->window->draw(this->playerHpBar);
	this->window->draw(this->shield);
}

void Game::renderBackground()
{
	this->window->draw(this->worldBackground);
}

void Game::renderWelcomeScreen()
{
	//clear old frame
	this->window->clear();

	//loading new things 
	this->renderBackground();
	this->window->draw(this->welcomeBackground);
	this->window->draw(this->highscoreText);

	//pushing new frame!
	this->window->display();
}

void Game::render()
{
	//clear the old frame
	this->window->clear();

	//add elements to render next
	this->renderBackground();
	//add objects
	this->ship->render(*this->window);
	
	//for bullets
	for (auto* bullet : this->bulletNum)
	{
		bullet->render(this->window);
	}
	
	//for each enemy
	for (auto* enemy : this->enemyNum)
	{
		enemy->render(this->window);
	}

	//HUD render
	this->renderHUD();

	//Rendering Game Over Screen
	if (this->ship->getHp() == 0 || this->sh.getHp() == 0)
	{
		this->window->draw(this->gameOverText);
		this->window->draw(this->highscoreText);
	}

	//push the new frame
	this->window->display();
}
