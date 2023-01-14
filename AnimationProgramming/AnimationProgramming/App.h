#pragma once
#include "Animator.h"


class App
{
	int stepAnimationCrossFade;

	float lerpCrossFade;
	float speedLerpCrossFade;

	Body* body;
	Animator* animator;
	std::vector<float> matriceArray;
	std::vector<Animation*> animations;

public:
	App();
	~App();

	void Update(float deltaTime);
	void UpdateKeyFrame(float deltaTime);
};