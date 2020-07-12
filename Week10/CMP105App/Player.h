#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework/Vector.h"
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>

class Player : public GameObject {
public:

	bool justPressedL;
	bool isJumping;
	float scale;
	sf::Texture texture;
	sf::Vector2f gravity;

	Player();
	~Player();

	void handleInput(float dt);
	void update(float dt);
	void collisionResponse(GameObject* collider);
};