#pragma once
#include <vector>

#include "Engine.h"
#include "Transform.h"


class Bone
{
	int boneIndex;
	int parentBoneIndex;
	Bone* parentBone;

public:
	Bone();

	const char* boneName;
	std::vector<Bone*> children;
	Transform localBindPose, worldBindPose;

	inline void SetIndex(int index) { boneIndex = index; }
	inline void SetParentIndex(int index) { parentBoneIndex = index; }
	inline void SetParent(Bone* parent) { parentBone = parent; }
	
	inline int GetIndex() { return boneIndex; }
	inline int GetParentIndex() { return parentBoneIndex; }

	inline Bone* GetParent() { return parentBone; }
};