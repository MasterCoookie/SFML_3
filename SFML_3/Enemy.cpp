#include "Enemy.h"

Enemy::Enemy(float pos_x, float pos_y) {
	this->initVariables();
	this->initShape();

	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy() {

}

const sf::Vector2f& Enemy::getPosition() const {
	return this->shape.getPosition();
}

const sf::FloatRect Enemy::getBounds() const {
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const{
	return this->points;
}

const int& Enemy::getDmg() const {
	return this->dmg;
}

void Enemy::update() {
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target) {
	target->draw(this->shape);
}

void Enemy::initVariables() {
	this->pointCount = rand() % 8 + 3;
	this->type = 0;
	this->hpMax = static_cast<int>(this->pointCount) / 2;
	this->hp = hpMax;
	this->dmg = this->hpMax;
	this->points = this->pointCount;
	this->speed = static_cast<float>(this->pointCount / 3);
}

void Enemy::initShape() {
	this->shape.setRadius(this->pointCount*4);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}
