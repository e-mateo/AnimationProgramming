#pragma once
#include "Bone.h"


class Body
{
	int bonesCount;
	Bone* rootBone;
	std::vector<Bone*> bones;

public:
	Body();
	~Body();

	void RootSetup();
	void BoneSetup();
	void ParentSetup();
	void SetRoot(Bone* root);
	void AddBone(Bone* bone);
	void SetBonesCount(int bones);
	void CalculateWorldBindPose(Bone* bone);

	inline int GetBonesCount() { return bonesCount; }
	inline Bone* GetRootBone() { return rootBone; }
	inline Bone* GetBone(int id) { return bones[id]; }
};