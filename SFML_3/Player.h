#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

class Player {
private:
	sf::Texture texture;
	sf::Sprite sprite;

	float movementSpeed;
	int hpMax;
	int hp;

	float attackCooldown;
	float attackCooldownMax;

	//private functions
	void initTexture();
	void initSprite();
	void initVariables();
public:
	Player();
	~Player();

	void update();
	void updateAttack();
	void render(sf::RenderTarget& target);

	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getBounds() const;
	const int getHpMax() const;
	const int getHp() const;

	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);

	void move(const float dirX, const float dirY);
	const bool canAttack();
	void takeDmg(int dmg);
};

