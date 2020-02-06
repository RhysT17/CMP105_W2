#include "Level.h"
#include <iostream>
#include <cmath>
using namespace std;

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	circle.setPosition(sf::Vector2f(100, 100));
	circle.setRadius(40.0f);
	circle.setFillColor(sf::Color::Black);

	mouseFont.loadFromFile("font/arial.ttf");
	mouseData.setPosition(sf::Vector2f(100, 100));
	mouseData.setFillColor(sf::Color::Black);
	mouseData.setFont(mouseFont);
	mouseData.setString("0  0");
	mouseX = "1";
	mouseY = "1";

	dragCoordsInitial.x = 0;
	dragCoordsInitial.y = 0;
	dragCoordsEnd.x = 0;
	dragCoordsEnd.y = 0;
	dragDistance = 0;
	dragChecked = true;
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::W))
	{
		input->setKeyUp(sf::Keyboard::W);
		cout << "W" << endl;
	}

	if (input->isKeyDown(sf::Keyboard::J) && input->isKeyDown(sf::Keyboard::K) && input->isKeyDown(sf::Keyboard::L))
	{
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		cout << "J:K:L" << endl;
	}

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();
	}

	if (input->isMouseLDown() && dragChecked)
	{
		dragChecked = false;
		dragCoordsInitial.x = input->getMouseX();
		dragCoordsInitial.y = input->getMouseY();
	}

	if (!input->isMouseLDown())
	{
		dragCoordsEnd.x = input->getMouseX();
		dragCoordsEnd.y = input->getMouseY();
		calculateDrag();
	}

	if (input->isMouseRDown())
	{
		circle.setPosition(sf::Vector2f(input->getMouseX() - 20, input->getMouseY() - 20));
	}
}

// Update game objects
void Level::update()
{
	mouseX = to_string(input->getMouseX());
	mouseY = to_string(input->getMouseY());
	mouseData.setString(mouseX + "  " + mouseY);
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(mouseData);
	window->draw(circle);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}

void Level::calculateDrag()
{
	dragDistance = (sqrt(pow(dragCoordsInitial.x - dragCoordsEnd.x, 2) + pow(dragCoordsInitial.y - dragCoordsEnd.y, 2)));
	cout << dragDistance << endl;
	dragChecked = true;
}