#pragma once
class Simulation;

class StateManager
{
public:
	virtual ~StateManager() = default;

	virtual void onCreate(Simulation& simulation) = 0;
	virtual void onClose(Simulation& simulation) = 0;
};