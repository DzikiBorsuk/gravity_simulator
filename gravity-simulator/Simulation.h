#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include "Box2d.h"

#include "State.h"
#include <list>
#include <thread>


class Simulation
{
public:
	Simulation();
	~Simulation();

	std::list<std::thread> threads;

	sf::RenderWindow window;
	sf::Event event;
	sf::Vector2i mousePos;
	sf::Vector2i lastMousePos;
	sf::Vector2f relativeMousePos;
	float deltaTime;
	float timeStepMultiplier;
	
	b2World world;

	void run();
	void changeState();
	void waitForThreads();

private:
	std::unique_ptr<State> currentState;
	std::chrono::high_resolution_clock timer;

	void handleEvent();
	void render();
	void update();
};
