#include "Animation.h"


Animation::Animation(Body* animBody)
{
	body = animBody;
	animName = " ";

	curFrame = 0;
	nextFrame = 0;
	animSpeed = 20.f;
	currentFrame = 0.f;
	keyFrameCount = 0;

	animLocal.clear();
	animWorld.clear();
}

Animation::Animation(const char* name, const int frameCount, Body* animBody)
{
	animName = name;
	keyFrameCount = frameCount;
	body = animBody;

	curFrame = 0;
	nextFrame = 0;
	animSpeed = 20.f;
	currentFrame = 0.f;

	animLocal.clear();
	animWorld.clear();

	//Get Local Anim
	for (int bonesIndex = 0; bonesIndex < body->GetBonesCount(); bonesIndex++)
		SetupLocalAnimMatrix(bonesIndex, animBody->GetBone(bonesIndex));

	//Create World anim for root bone
	std::vector<Transform> rootWorldAnim;
	for (int i = 0; i < keyFrameCount; i++)
		rootWorldAnim.push_back(animLocal[0][i]);
	animWorld.push_back(rootWorldAnim);

	//Set World anim for each bone
	for (int i = 0; i < animBody->GetRootBone()->children.size(); i++)
		CalculateWorldAnimMatrix(animBody->GetRootBone()->children[i]->GetIndex(), animBody->GetRootBone()->children[i]);
}

Animation::~Animation() {}

void Animation::UpdateFrame(float deltaTime)
{
	currentFrame += deltaTime * animSpeed;

	if (currentFrame >= keyFrameCount)
		currentFrame = 0;

	curFrame = (int)currentFrame;
	nextFrame = curFrame + 1;

	if (curFrame >= keyFrameCount - 1)
		nextFrame = 0;
}

void Animation::SetupLocalAnimMatrix(int boneIndex, Bone* bone)
{
	Transform localAnim;
	std::vector<Transform> localAnimEveryFrame;
	for (int keyFrameIndex = 0; keyFrameIndex < keyFrameCount; keyFrameIndex++)
	{
		GetAnimLocalBoneTransform(animName, boneIndex, keyFrameIndex, localAnim.pos.x, localAnim.pos.y, localAnim.pos.z, localAnim.rot.w, localAnim.rot.x, localAnim.rot.y, localAnim.rot.z);
		localAnimEveryFrame.push_back(localAnim);
	}
	animLocal.push_back(localAnimEveryFrame);
}

void Animation::CalculateWorldAnimMatrix(int boneIndex, Bone* bone)
{
	Transform world;
	std::vector<Transform> worldAnimEveryFrame;
	maths::Mat4 localBindPoseTransform = maths::CreateTransformMatrix(bone->localBindPose.rot, bone->localBindPose.pos);
	maths::Mat4 animLocalTransform, animWorldParentTransform;

	for (int keyFrameIndex = 0; keyFrameIndex < keyFrameCount; keyFrameIndex++)
	{
		animLocalTransform = maths::CreateTransformMatrix(animLocal[bone->GetIndex()][keyFrameIndex].rot, animLocal[bone->GetIndex()][keyFrameIndex].pos);
		animWorldParentTransform = maths::CreateTransformMatrix(animWorld[bone->GetParentIndex()][keyFrameIndex].rot, animWorld[bone->GetParentIndex()][keyFrameIndex].pos);

		maths::Mat4 worldAnim = animWorldParentTransform * localBindPoseTransform * animLocalTransform;
		maths::Vec4 pos = worldAnim * maths::Vec4(0.f, 0.f, 0.f, 1.f);
		pos.FillVec3(&world.pos);
		world.rot = maths::Mat4ToQuaternion(worldAnim);
		worldAnimEveryFrame.push_back(world);
	}

	animWorld.push_back(worldAnimEveryFrame);

	for (int i = 0; i < bone->children.size(); i++)
		CalculateWorldAnimMatrix(bone->children[i]->GetIndex(), bone->children[i]);
}

void Animation::SetSpeedAnim(float speed)
{
	animSpeed = speed;
}

void Animation::SetUpperArmTransform(int frame, maths::Vec3& pos, maths::Quat& rot)
{
	float angle = maths::PI / 16.f;

	maths::Quat quat;
	pos = maths::Vec3(0, 0, 0);

	if (frame < 8)
	{
		float start = -maths::PI / 3.0f;
		rot = quat.AxisAngle2Quat(maths::Vec3(0, 0, 1), (start + (angle * frame))).Normalize();

	}
	else if (frame < 16)
	{
		float start = -maths::PI / 3.0f + (angle * 7.0f);
		rot = quat.AxisAngle2Quat(maths::Vec3(0, 0, 1), (start - angle * (frame - 8.0f))).Normalize();
	}
}

void Animation::CreateOwnAnimation()
{
	animName = "OwnAnimation";
	keyFrameCount = 16;

	int upperArmLeftIndex = GetSkeletonBoneIndex("upperarm_l");
	int upperArmRightIndex = GetSkeletonBoneIndex("upperarm_r");

	for (int bonesIndex = 0; bonesIndex < body->GetBonesCount(); bonesIndex++)
	{
		Transform localAnim;
		std::vector<Transform> localAnimEveryFrame;
		for (int keyFrameIndex = 0; keyFrameIndex < keyFrameCount; keyFrameIndex++)
		{
			localAnim.pos = maths::Vec3(0, 0, 0);
			localAnim.rot = maths::Quat(0, 0, 0, 1);

			if (bonesIndex == upperArmLeftIndex || bonesIndex == upperArmRightIndex)
				SetUpperArmTransform(keyFrameIndex, localAnim.pos, localAnim.rot);

			localAnimEveryFrame.push_back(localAnim);
		}
		animLocal.push_back(localAnimEveryFrame);
	}

	//Create World anim for root bone
	std::vector<Transform> rootWorldAnim;
	for (int i = 0; i < keyFrameCount; i++)
		rootWorldAnim.push_back(animLocal[0][i]);
	animWorld.push_back(rootWorldAnim);

	//Set World anim for each bone
	for (int i = 0; i < body->GetRootBone()->children.size(); i++)
		CalculateWorldAnimMatrix(body->GetRootBone()->children[i]->GetIndex(), body->GetRootBone()->children[i]);
}