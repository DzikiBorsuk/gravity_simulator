#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include "Box2D/Dynamics/b2Body.h"

class Simulation;

class Planet : public sf::Drawable
{
	sf::CircleShape planetModel;
	b2Body* planetObject;

public:
	Planet(Simulation& simulation,const float& size,const b2Vec2 pos);
	~Planet();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update();

	b2Vec2 getPosition() const;
	b2Body* getPlanetPointer() const;
	void setPlanetPointer(b2Body& planet) const;

	//static Planet mergePlanet(Planet A, Planet B);
};

