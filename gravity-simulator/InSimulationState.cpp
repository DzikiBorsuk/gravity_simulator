#include "InSimulationState.h"
#include "Simulation.h"
#include "Globals.h"


void InSimulationState::CalculateForces()
{
	for (auto& a : planets)
	{
		b2Vec2 accelerationVector(0.f, 0.f);
		for (auto& b : planets)
		{
			if (a != b)
			{
				auto distantVector = b->getPosition() - a->getPosition();
				auto angle = acosf(distantVector.x / distantVector.Length())*sgn(distantVector.y);

				auto acceleration = (Global_Parameters::gravityConst*a->getPlanetPointer()->GetMass()*b->getPlanetPointer()->GetMass())
					/ distantVector.LengthSquared();

				auto x = acceleration*cosf(angle);
				auto y = acceleration*sinf(angle);

				b2Vec2 temp(x, y);
				accelerationVector += temp;
			}
		}

		a->getPlanetPointer()->ApplyForceToCenter(accelerationVector, true);
	}
}

void InSimulationState::placeNewPlanet(Simulation& simulation)
{
	auto planetTemplatePos = planetTemplate.getPosition() / Global_Parameters::worldScale;
	b2Vec2 pos(planetTemplatePos.x, planetTemplatePos.y);
	planets.push_back(std::make_shared<Planet>(simulation, size, pos));

	auto velocityVecotor = line[1].position - line[0].position;
	velocityVecotor /= Global_Parameters::worldScale;
	auto realVelocityVecotr = b2Vec2(velocityVecotor.x, velocityVecotor.y);

	planets.back()->getPlanetPointer()->SetLinearVelocity(realVelocityVecotr);
}

void InSimulationState::mousePressed(Simulation& simulation)
{
	isMousePressed = true;
	planetTemplate.setPosition(static_cast<sf::Vector2f>(simulation.relativeMousePos));
	line[0] = static_cast<sf::Vector2f>(simulation.relativeMousePos);
	line[1] = static_cast<sf::Vector2f>(simulation.relativeMousePos);
}

void InSimulationState::mouseReleased(Simulation& simulation)
{
	placeNewPlanet(simulation);
	isMousePressed = false;
	planetTemplate.setPosition(static_cast<sf::Vector2f>(simulation.relativeMousePos));
}

void InSimulationState::mouseScrolled(Simulation& simulation)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		size += 0.1*size*simulation.event.mouseWheelScroll.delta;
		if (size <= 0.001f)
			size = 0.002f;
		planetTemplate.setRadius(size*Global_Parameters::worldScale);
		planetTemplate.setOrigin(planetTemplate.getLocalBounds().width / 2,
			planetTemplate.getLocalBounds().height / 2);
		return;
	}
	auto view = simulation.window.getView();
	if (view.getSize().x >= 160 * 2)
		view.setSize(view.getSize() - view.getSize()*0.1f*simulation.event.mouseWheelScroll.delta);
	else
		view.setSize(sf::Vector2f(160 * 2, 90 * 2));
	simulation.window.setView(view);
}

void InSimulationState::changeView(Simulation& simulation)
{
	auto view = simulation.window.getView();
	auto offset = simulation.mousePos - simulation.lastMousePos;
	auto scale = simulation.window.getView().getSize().x / simulation.window.getSize().x;
	view.setCenter(view.getCenter() - static_cast<sf::Vector2f>(offset)*scale);
	simulation.window.setView(view);
}

void InSimulationState::mouseMove(Simulation& simulation)
{
	if (!isMousePressed)
		planetTemplate.setPosition(static_cast<sf::Vector2f>(simulation.relativeMousePos));
	else
	{
		line[1] = static_cast<sf::Vector2f>(simulation.relativeMousePos);
	}
}

InSimulationState::InSimulationState() : size(0.05f), planetTemplate(0.05f*Global_Parameters::worldScale),
line(sf::Lines, 2), isMousePressed(false)
{
	planetTemplate.setOrigin(planetTemplate.getLocalBounds().width / 2,
		planetTemplate.getLocalBounds().height / 2);
	planetTemplate.setFillColor(sf::Color(0, 255, 0, 128));
	line[0].color = sf::Color::Yellow;
	line[1].color = sf::Color::Yellow;
}


InSimulationState::~InSimulationState()
{
}

void InSimulationState::onCreate(Simulation& simulation)
{
}

void InSimulationState::onClose(Simulation& simulation)
{
}

void InSimulationState::handleEvent(Simulation& simulation)
{

	switch (simulation.event.type)
	{
	case sf::Event::KeyPressed:
		if (simulation.event.key.code == sf::Keyboard::R)
			planets.clear();
		break;
	case sf::Event::MouseButtonPressed:
		if (simulation.event.mouseButton.button == sf::Mouse::Button::Left)
			mousePressed(simulation);
		break;
	case sf::Event::MouseButtonReleased:
		if (simulation.event.mouseButton.button == sf::Mouse::Button::Left)
			mouseReleased(simulation);
		break;
	case sf::Event::MouseWheelScrolled:
		mouseScrolled(simulation);
		break;
	case sf::Event::MouseMoved:
		if (sf::Mouse().isButtonPressed(sf::Mouse::Button::Middle))
			changeView(simulation);
		mouseMove(simulation);
		break;
	default:;
	}
}

void InSimulationState::update(Simulation& simulation)
{
	CalculateForces();

	for (auto& element : planets)
	{
		element->update();
	}
}

void InSimulationState::render(Simulation& simulation)
{
	for (const auto& element : planets)
	{
		simulation.window.draw(*element);
	}
	simulation.window.draw(planetTemplate);
	if (isMousePressed)
		simulation.window.draw(line);
}
