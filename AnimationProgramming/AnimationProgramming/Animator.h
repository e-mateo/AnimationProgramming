#pragma once
#include "Animation.h"


class Animator
{
	int indexAnimIn;
	int indexAnimOut;

	maths::Vec3 color;
	std::vector<maths::Vec3> finalPosition;

public:
	Animator();
	~Animator();

	void SetAnimInAndOut(const int stepAnim);
	void DrawSkeleton(Body* body, int curFrame);
	void Animate(std::vector<float>& matriceArray, Body* body,const std::vector<Animation*> animation, const float lerpCrossFade);

	Transform CrossFade(Transform anim1, Transform anim2, float lerp);
	Transform Blend(Transform bone1, Transform bone2, int keyFrame1, int keyFrame2, float frame);
};