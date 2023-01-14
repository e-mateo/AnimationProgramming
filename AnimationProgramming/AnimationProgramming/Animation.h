#pragma once
#include "Body.h"


class Animation
{
	const char* animName;

	int curFrame;
	int nextFrame;
	int keyFrameCount;

	float animSpeed;
	float currentFrame;

	std::vector<std::vector<Transform>> animLocal;  //  animLocal[boneIndex][frame]
	std::vector<std::vector<Transform>> animWorld; //   animWorld[boneIndex][frame]

	Body* body;

	void SetUpperArmTransform(int frame, maths::Vec3& pos, maths::Quat& rot);
	void SetupLocalAnimMatrix(int boneIndex,  Bone* bone);
	void CalculateWorldAnimMatrix(int boneIndex, Bone* bone);

public:
	Animation(Body* animBody);
	Animation(const char* name, const int frameCount, Body* animBody);
	~Animation();

	void CreateOwnAnimation();
	void SetSpeedAnim(float speed);
	void UpdateFrame(float deltaTime);

	inline int GetCurFrame() { return curFrame; }
	inline int GetNextFrame() { return nextFrame; }
	inline int GetKeyframeCount() { return keyFrameCount; }

	inline float GetSpeed() { return animSpeed; }
	inline float GetCurFloatFrame() { return currentFrame; }

	inline std::vector<std::vector<Transform>> GetAnimWorld() { return animWorld; }
};