#include "Planet.h"
#include "Globals.h"
#include "Simulation.h"


Planet::Planet(Simulation& simulation, const float& size, const b2Vec2 pos) :
	planetModel(size*Global_Parameters::worldScale,100), planetObject(nullptr)
{
	planetModel.setFillColor(sf::Color::Green);
	planetModel.setOrigin(planetModel.getLocalBounds().width / 2,
		planetModel.getLocalBounds().height / 2);
	planetModel.setPosition(pos.x*Global_Parameters::worldScale, pos.y*Global_Parameters::worldScale);

	b2BodyDef planetDef;
	planetDef.type = b2_dynamicBody;
	planetDef.position = pos;

	planetObject = simulation.world.CreateBody(&planetDef);

	b2CircleShape planet;
	planet.m_radius = size;

	b2FixtureDef planetFixture;
	planetFixture.shape = &planet;
	planetFixture.density = 1.f;
	planetFixture.friction = 0.f;

	planetObject->CreateFixture(&planetFixture);
}


Planet::~Planet()
{
	planetObject->DestroyFixture(planetObject->GetFixtureList());
}

void Planet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(planetModel);
}

void Planet::update()
{
	auto pos = planetObject->GetPosition();

	pos *= Global_Parameters::worldScale;

	planetModel.setPosition(pos.x, pos.y);
}

b2Vec2 Planet::getPosition() const
{
	return planetObject->GetPosition();
}

b2Body* Planet::getPlanetPointer() const
{
	return planetObject;
}

void Planet::setPlanetPointer(b2Body& planet) const
{
	*planetObject = std::move(planet);
}

//Planet Planet::mergePlanet(Planet A, Planet B)
//{
//}
