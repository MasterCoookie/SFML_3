#include "Game.h"


Game::Game() {
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initPlayer();
	this->initEnemies();
	this->initSystems();
}

Game::~Game() {
	delete this->window;
	delete this->player;

	//delete textures
	for(auto &tex : this->textures) {
		delete tex.second;
	}

	//delete bullets
	for (auto& bullet : this->bullets) {
		delete bullet;
	}

	//delete enemies
	for (auto& enemy : this->enemies) {
		delete enemy;
	}
}

void Game::run() {
	while (this->window->isOpen()) {
		this->pollEvents();
		if (this->player->getHp() > 0) {
			this->update();
			this->render();
		}
		
	}
}

void Game::initWindow() {
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Gejm 3", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer() {
	this->player = new Player();
}

void Game::initEnemies() {
	this->spawnTimerMax = 50;
	this->spawnTimer = spawnTimerMax;
}

void Game::initTextures() {
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/missileTex01.png");
}

void Game::initGUI() {
	if (!this->font.loadFromFile("./Fonts/IndieFlower-Regular.ttf")) {
		std::cout << " ! ERR: GAME::INITGUI: Failed to load font! " << std::endl;
	}
	this->pointText.setPosition(700.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Loading");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f
	);

	//init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld() {
	if (!this->worldBcgText.loadFromFile("./Textures/space.jpg")) {
		std::cout << " ! ERR: GAME::INITWORLD: could not load bcg img" << std::endl;
	}
	this->worldBcg.setTexture(this->worldBcgText);
}

void Game::initSystems() {
	this->points = 0;
}

void Game::pollEvents() {
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed) {
			this->window->close();
		}
		else if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape) {
			this->window->close();
		}
	}
}

void Game::updateInput() {
	//move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		this->player->move(-1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		this->player->move(1.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		this->player->move(0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		this->player->move(0.f, 1.f);
	}

	//shoot
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack()) {
		this->bullets.push_back(new Bullet(this->textures["BULLET"], 0.f, -1.f,
			(this->player->getPosition().x + this->player->getBounds().width / 2.f) - 5.7,
			this->player->getPosition().y,
		5.f));
	}
}

void Game::updateBullets() {

	size_t counter = 0;
	for (auto* bullet : bullets) {
		bullet->update();

		//bullet culling top of screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
			//remove bullet thats not on screen
			delete this->bullets.at(counter);
			this -> bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Game::updateEnemies() {
	//spawning
	this->spawnTimer += .5f;
	if (this->spawnTimer >= spawnTimerMax) {
		this->enemies.push_back(new Enemy(rand()%this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	size_t counter = 0;
	for (auto* enemy : enemies) {
		enemy->update();

		//enemy culling bottom of screen
		if (enemy->getBounds().top > this->window->getSize().y) {
			//remove enemy not on screen
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		} else if(enemy->getBounds().intersects(this->player->getBounds())) {

			this->player->takeDmg(enemy->getDmg());

			//remove enemy crashed at player
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}



		++counter;

	}
	
}

void Game::updateCombat() {
	for (size_t i = 0; i < this->enemies.size(); ++i) {
		bool enemy_deleted = false;
		for (size_t j = 0; j < this->bullets.size() && !enemy_deleted; ++j) {
			if (bullets[j]->getBounds().intersects(this->enemies[i]->getBounds())) {

				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);
				enemy_deleted = true;
			}
		}
	}
}

void Game::update() {
	
	this->updateInput();
	this->updateCollision();
	this->player->update();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
	this->updateWorld();
}

void Game::updateGUI() {
	std::stringstream ss;
	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	//update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y ));
}

void Game::updateWorld() {
}

void Game::updateCollision() {
	//LEFT-RIGHT clipping
	if (this->player->getBounds().left < 0.f) {
		this->player->setPosition(0.f, this->player->getBounds().top);
	} else if (this->player->getBounds().left + this->player->getBounds().width > this->window->getSize().x) {
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//TOP-BOTTOM clipping
	if (this->player->getBounds().top < 0.f) {
		this->player->setPosition(this->player->getPosition().x, 0.f);
	}
	else if (this->player->getBounds().top + this->player->getBounds().height > this->window->getSize().y) {
		this->player->setPosition(this->player->getPosition().x, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::render() {
	this->window->clear();

	//draw stuff here
	this->renderWorld();

	this->player->render(*this->window);
	for (auto& bullet : bullets) {
		bullet->render(this->window);
	}
	
	for (auto& enemy : enemies) {
		enemy->render(this->window);
	}
	this->renderGUI();

	//gameover screen
	if (this->player->getHp() <= 0) {
		this->window->draw(this->gameOverText);
	}

	this->window->display();
}

void Game::renderWorld() {
	this->window->draw(this->worldBcg);
}

void Game::renderGUI() {
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}
