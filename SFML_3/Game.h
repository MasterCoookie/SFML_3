#pragma once
#include <map>
#include <string>
#include <sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game {
public: 
	Game();
	~Game();

	void run();
	
private:
	//window
	sf::RenderWindow* window;

	// Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	Player* player;

	//Enemeis
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//GUI
	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;

	//player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//World
	sf::Texture worldBcgText;
	sf::Sprite worldBcg;

	//systems
	unsigned points;

	//private funcitons
	void initWindow();
	void initPlayer();
	void initEnemies();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();
	
	void pollEvents();

	void updateInput();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void update();


	void render();
	void renderWorld();
	void renderGUI();
};

