#include "Bone.h"


Bone::Bone()
{
	boneName = "";

	boneIndex = -1;
	parentBoneIndex = -1;

	parentBone = nullptr;
}