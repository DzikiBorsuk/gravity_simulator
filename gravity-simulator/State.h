#pragma once
#include "StateManager.h"

class State : public StateManager
{
public:
	State() = default;
	virtual ~State() = default;

	virtual void handleEvent(Simulation& simulation) = 0;
	virtual void update(Simulation& simulation) = 0;
	virtual void render(Simulation& simulation) = 0;
};