// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "Maths.h"
#include "stdafx.h"
#include "Engine.h"
#include "Simulation.h"


class CSimulation : public ISimulation
{
	virtual void Init() override
	{
		app = new App();
	}

	virtual void Update(float deltaTime) override
	{
		/// GIZMO ///
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);

		app->Update(deltaTime);
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

	delete simulation.app;
	return 0;
}