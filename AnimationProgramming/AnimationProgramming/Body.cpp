#include "Body.h"


Body::Body()
{
	bones.clear();
	bonesCount = 0;
	rootBone = nullptr;
}

Body::~Body()
{
	for (int i = 0; i < bones.size(); i++)
		delete bones[i];
}

void Body::SetBonesCount(int bones)
{
	bonesCount = bones;
}

void Body::SetRoot(Bone* root)
{
	rootBone = root;
}

void Body::AddBone(Bone* bone)
{
	bones.push_back(bone);
}

void Body::RootSetup()
{
	Bone* root = new Bone();
	root->SetIndex(0);
	root->SetParent(nullptr);
	root->boneName = GetSkeletonBoneName(0);
	GetSkeletonBoneLocalBindTransform(0, root->localBindPose.pos.x, root->localBindPose.pos.y, root->localBindPose.pos.z, root->localBindPose.rot.w, root->localBindPose.rot.x, root->localBindPose.rot.y, root->localBindPose.rot.z);
	root->worldBindPose = root->localBindPose;

	rootBone = root;
	AddBone(root);
}

void Body::BoneSetup()
{
	for (int boneIndex = 1; boneIndex < bonesCount; boneIndex++)
	{
		Bone* bone = new Bone();
		bone->SetIndex(boneIndex);
		bone->SetParentIndex(GetSkeletonBoneParentIndex(boneIndex));
		bone->boneName = GetSkeletonBoneName(boneIndex);
		GetSkeletonBoneLocalBindTransform(boneIndex, bone->localBindPose.pos.x, bone->localBindPose.pos.y, bone->localBindPose.pos.z, bone->localBindPose.rot.w, bone->localBindPose.rot.x, bone->localBindPose.rot.y, bone->localBindPose.rot.z);
		AddBone(bone);
	}
}

void Body::ParentSetup()
{
	for (int i = 1; i < bonesCount; i++)
	{
		bones[i]->SetParent(bones[bones[i]->GetParentIndex()]);
		bones[i]->GetParent()->children.push_back(bones[i]);
	}
}

void Body::CalculateWorldBindPose(Bone* bone)
{
	maths::Mat4 parentWorldBindPose = maths::CreateTransformMatrix(bone->GetParent()->worldBindPose.rot, bone->GetParent()->worldBindPose.pos);
	maths::Mat4 localBindPose = maths::CreateTransformMatrix(bone->localBindPose.rot, bone->localBindPose.pos);
	maths::Mat4 worldBindPose = parentWorldBindPose * localBindPose;

	maths::Vec4 pos = worldBindPose * maths::Vec4(0.f, 0.f, 0.f, 1.f);
	pos.FillVec3(&bone->worldBindPose.pos);
	bone->worldBindPose.rot = maths::Mat4ToQuaternion(worldBindPose);

	for (int i = 0; i < bone->children.size(); i++)
		CalculateWorldBindPose(bone->children[i]);
}