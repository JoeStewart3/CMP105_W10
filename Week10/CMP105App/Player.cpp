#include "Player.h"

Player::Player() {
	justPressedL = false;
	isJumping = true;
	velocity.x = 0;
	velocity.y = 0;
	scale = 200.f;
	gravity = sf::Vector2f(0, 9.8f) * scale;
}
Player::~Player() {}

void Player::handleInput(float dt) {

	// Movement
	
	if (input->isKeyDown(sf::Keyboard::D) == false && input->isKeyDown(sf::Keyboard::A) == false) {
		velocity.x = 0;
	}
	if (input->isKeyDown(sf::Keyboard::D)) {
		//std::cout << "Right pressed";
		velocity.x = 500;
	}
	if (input->isKeyDown(sf::Keyboard::A)) {
		//std::cout << "Left pressed";
		velocity.x = -500;
	}
	if (isJumping == false) {
		if (input->isKeyDown(sf::Keyboard::W)) {
			velocity.y = -1000;
			isJumping = true;
			input->setKeyUp(sf::Keyboard::W);
		}
	}
}


void Player::update(float dt) {
	//std::cout << std::to_string(getPosition().x) + ", " + std::to_string(getPosition().y) << std::endl;
	
		//Apply gravity force, increasing velocity
		//Move shape by this new velocity
		sf::Vector2f pos = velocity * dt + 0.5f * gravity * dt * dt; // ut + 1/2at^2
		velocity += gravity * dt; // v = u + at 
		setPosition(getPosition() + pos);

		//Check if ball is touching floor
		//If ball hits the floor, make it bounce in the opposite direction
		if (getPosition().y > 555) {
			setPosition(getPosition().x, 555);
			velocity.y = (-velocity.y) / 1.8f;
			//If player is touching the ground, they're not jumping
			isJumping = false;
		}
		if (getPosition().y < 0) {
			setPosition(getPosition().x, 0);
			velocity.y = (-velocity.y) / 1.2f;
		}
		if (getPosition().x > 1200) {
			setPosition(1200, getPosition().y);
			velocity.x = (-velocity.x) / 1.2f;
		}
		if (getPosition().x < 0) {
			setPosition(0, getPosition().y);
			velocity.x = (-velocity.x) / 1.2f;
		}
}

void Player::collisionResponse(GameObject* collider) {

	//Coordinates of the centre of the collider and of the player
	sf::Vector2f colliderCentre = (collider->getPosition() + (collider->getSize() * 0.5f));
	sf::Vector2f playerCentre = (getPosition() + (getSize() * 0.5f));
	playerCentre = sf::Vector2f(playerCentre.x, playerCentre.y + 1.f);

	//X and Y for finding direction
	sf::Vector2f diff;
	diff.x = colliderCentre.x - playerCentre.x;
	diff.y = colliderCentre.y - playerCentre.y;

	//Check if hit is top/bottom or left/right
	//abs() makes sure all values are positive
	if (std::abs(diff.x) > std::abs(diff.y)){
		std::cout << "SIDE COLLISION ON ";
		//left side collision
		if (colliderCentre.x > playerCentre.x){
			std::cout << "LEFT" << std::endl;
			velocity.x = 0;
			setPosition(collider->getPosition().x - getSize().x, getPosition().y);
		}
		//right side collision
		if (colliderCentre.x < playerCentre.x){
			std::cout << "RIGHT" << std::endl;
			velocity.x = 0;
			setPosition(collider->getPosition().x + getSize().x, getPosition().y);
		}
	}
	else{
		std::cout << "TOP/BOTTOM COLLISION ON ";
		//top side collision
		if (colliderCentre.y > playerCentre.y){
			std::cout << "TOP" << std::endl;
			velocity.y = 0;
			setPosition(getPosition().x, collider->getPosition().y - getSize().y);
		}
		//bottom side collision
		if (colliderCentre.y < playerCentre.y) {
			std::cout << "BOTTOM" << std::endl;
			velocity.y = 0;
			setPosition(getPosition().x, collider->getPosition().y + getSize().y);
		}
	}
}