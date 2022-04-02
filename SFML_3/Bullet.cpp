#include "Bullet.h"

Bullet::Bullet() {};

Bullet::Bullet(sf::Texture* texture, float dir_x, float dir_y, float pos_x, float pos_y, float movement_speed) : movementSpeed(movement_speed) {
	this->shape.setTexture(*texture);
	this->shape.setScale(.05f, .05f);
	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
}

Bullet::~Bullet() {

}

const sf::FloatRect Bullet::getBounds() const {
	return this->shape.getGlobalBounds();
}

void Bullet::update() {
	//movement
	this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target) {
	target->draw(this->shape);
}
