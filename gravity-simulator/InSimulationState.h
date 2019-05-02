#pragma once
#include "State.h"
#include <list>

#include "Planet.h"
#include <thread>

class InSimulationState : public State
{
	using PlanetPtr = std::shared_ptr<Planet>;

	float size;
	sf::CircleShape planetTemplate;
	sf::VertexArray line;
	std::list<PlanetPtr> planets;
	bool isMousePressed;


	void CalculateForces();

	void placeNewPlanet(Simulation& simulation);

	void mousePressed(Simulation& simulation);
	void mouseReleased(Simulation& simulation);
	void mouseScrolled(Simulation& simulation);
	void changeView(Simulation& simulation);
	void mouseMove(Simulation& simulation);
public:
	InSimulationState();
	~InSimulationState();

	void onCreate(Simulation& simulation) override;
	void onClose(Simulation& simulation) override;
	void handleEvent(Simulation& simulation) override;
	void update(Simulation& simulation) override;
	void render(Simulation& simulation) override;
};
