#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <vector>

#include "App.h"
#include "Engine.h"


class ENGINE_API ISimulation
{
public:
	virtual ~ISimulation() {}

	App* app;

	virtual void Init() {}
	virtual void Update(float deltaTime) {}
};
#endif