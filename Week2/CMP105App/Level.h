#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput();
	void update();
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	// Add your object here
	sf::CircleShape circle;
	sf::Text mouseData;
	sf::Font mouseFont;
	sf::String mouseX, mouseY;
	sf::Vector2f dragCoordsInitial, dragCoordsEnd;
	float dragDistance;
	bool dragChecked;

	void calculateDrag();
};