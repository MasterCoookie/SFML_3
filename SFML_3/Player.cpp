#include "Player.h"

void Player::initTexture() {
	//load texture from file
	if (!this->texture.loadFromFile("./Textures/ship.png")) {
		std::cout << "ERR: PLAYER::INITTEXTURE: Could not load texture file" << std::endl;
	}
	
}

void Player::initSprite() {
	//set texture to sprite
	this->sprite.setTexture(this->texture);

	//resize sprite
	this->sprite.scale(.1f, .1f);
}

void Player::initVariables() {
	this->attackCooldownMax = 100.f;
	this->attackCooldown = this->attackCooldownMax;
	this->hpMax = 25;
	this->hp = hpMax;
}

Player::Player() : movementSpeed(2.f) {
	this->initTexture();
	this->initSprite();
	this->initVariables();
}

Player::~Player() {
	this->initVariables();
}

void Player::update() {
	this->updateAttack();
}

void Player::updateAttack() {
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 1.5f;
	}

}

void Player::render(sf::RenderTarget& target) {
	target.draw(this->sprite);
}

const sf::Vector2f& Player::getPosition() const {
	return  this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int Player::getHpMax() const{
	return this->hpMax;
}

const int Player::getHp() const {
	return this->hp;
}

void Player::setPosition(const sf::Vector2f pos) {
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y) {
	this->sprite.setPosition(x, y);
}

void Player::move(const float dirX, const float dirY) {
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack() {
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::takeDmg(int dmg) {
	if ((this->hp - dmg) >= 0) {
		this->hp -= dmg;
	} else {
		this->hp = 0;
	}
	std::cout << this->hp << "\n";
}
