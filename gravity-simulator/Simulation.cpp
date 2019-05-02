#include "Simulation.h"
#include "InSimulationState.h"
#include "Globals.h"

Simulation::Simulation() : window(sf::VideoMode(Global_Parameters::xWindowDimension, Global_Parameters::yWindowDimension), "Gravity"),
deltaTime(0), timeStepMultiplier(0), world(b2Vec2_zero),
currentState(std::make_unique<InSimulationState>(InSimulationState())), timer()
{
	window.setVerticalSyncEnabled(true);
	currentState->onCreate(*this);
}

Simulation::~Simulation()
{
}

void Simulation::run()
{
	while (window.isOpen())
	{
		auto start = timer.now();

		handleEvent();
		update();
		render();

		waitForThreads();

		auto stop = timer.now();

		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() / 1000.f;
	}
}

void Simulation::changeState()
{

}

void Simulation::waitForThreads()
{
	for (auto& element : threads)
	{
		element.join();
	}
}

void Simulation::handleEvent()
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:
			lastMousePos = mousePos;
			mousePos = sf::Mouse().getPosition(window);
			relativeMousePos = window.mapPixelToCoords(mousePos);
			break;
		default:;
		}
		currentState->handleEvent(*this);
	}
}

void Simulation::render()
{
	window.clear();
	currentState->render(*this);
	window.display();
}

void Simulation::update()
{
	const int velocityIt = 8;
	const int positionIt = 3;

	world.Step(deltaTime, velocityIt, positionIt);

	currentState->update(*this);

}