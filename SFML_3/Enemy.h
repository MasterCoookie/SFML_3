#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
	Enemy();
	Enemy(float pos_x, float pos_y);
	~Enemy();

	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDmg() const;

	void update();
	void render(sf::RenderTarget* target);
private:
	unsigned int pointCount;
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int dmg;
	int points;

	void initShape();
	void initVariables();
};

