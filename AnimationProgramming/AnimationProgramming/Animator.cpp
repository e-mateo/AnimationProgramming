#include "Animator.h"


Animator::Animator()
{
	indexAnimIn = 0;
	indexAnimOut = 1;
	finalPosition.clear();
	color = maths::Vec3(0,1,1);
}

Animator::~Animator() {}

void Animator::Animate(std::vector<float>& matriceArray, Body* body, const std::vector<Animation*> animations, const float lerpCrossFade)
{
	Transform InAnimBlend, OutAnimBlend, transformCrossFade;
	maths::Mat4 crossFadeMatrix, worldBindPoseMatrix;
	maths::Mat4 skinningMat;
	finalPosition.clear();

	for (int boneNumber = 0; boneNumber < body->GetBonesCount(); boneNumber++)
	{
		std::vector<Transform> InAnim, OutAnim;

		InAnim = animations[indexAnimIn]->GetAnimWorld()[boneNumber];
		OutAnim = animations[indexAnimOut]->GetAnimWorld()[boneNumber];
		InAnimBlend = Blend(InAnim[animations[indexAnimIn]->GetCurFrame()], InAnim[animations[indexAnimIn]->GetNextFrame()], animations[indexAnimIn]->GetCurFrame(), animations[indexAnimIn]->GetNextFrame(), animations[indexAnimIn]->GetCurFloatFrame());
		OutAnimBlend = Blend(OutAnim[animations[indexAnimOut]->GetCurFrame()], OutAnim[animations[indexAnimOut]->GetNextFrame()], animations[indexAnimOut]->GetCurFrame(), animations[indexAnimOut]->GetNextFrame(), animations[indexAnimOut]->GetCurFloatFrame());

		transformCrossFade = CrossFade(InAnimBlend, OutAnimBlend, lerpCrossFade);
		crossFadeMatrix = maths::CreateTransformMatrix(transformCrossFade.rot, transformCrossFade.pos);

		worldBindPoseMatrix = maths::CreateTransformMatrix(body->GetBone(boneNumber)->worldBindPose.rot, body->GetBone(boneNumber)->worldBindPose.pos);
		skinningMat = crossFadeMatrix * worldBindPoseMatrix.inverseMatrix();
		skinningMat.FillArray();

		for (int i = 0; i < 16; i++)
			matriceArray.push_back(skinningMat.matrixArray[i]);

		//Useful for skeleton
		maths::Vec4 pos = crossFadeMatrix * maths::Vec4(0, 0, 0, 1);
		finalPosition.push_back(maths::Vec3(pos.x, pos.y, pos.z));
	}
}

Transform Animator::Blend(Transform bone1, Transform bone2, int keyFrame1, int keyFrame2, float frame)
{
	Transform blendTransform;
	if (keyFrame2 < keyFrame1)
		keyFrame2 = keyFrame1 + 1.0f;

	float t = (frame - (float)keyFrame1) / ((float)keyFrame2 - (float)keyFrame1);

	blendTransform.pos = maths::Lerp<maths::Vec3>(bone1.pos, bone2.pos, t);
	blendTransform.rot = maths::Slerp(bone1.rot, bone2.rot, t).Normalize();

	return blendTransform;
}

Transform Animator::CrossFade(Transform anim1, Transform anim2, float lerp)
{
	Transform blendTransform;

	if (lerp > 1)
		lerp = 1;

	blendTransform.pos = maths::Lerp<maths::Vec3>(anim1.pos, anim2.pos, lerp);
	blendTransform.rot = maths::Slerp(anim1.rot, anim2.rot, lerp).Normalize();

	return blendTransform;
}

void Animator::SetAnimInAndOut(const int stepAnim)
{
	switch (stepAnim)
	{
	case 0:
		indexAnimIn = 0;
		indexAnimOut = 1;
		break;
	case 1:
		indexAnimIn = 1;
		indexAnimOut = 0;
		break;
	case 2:
		indexAnimIn = 0;
		indexAnimOut = 2;
		break;
	case 3:
		indexAnimIn = 2;
		indexAnimOut = 0;
		break;
	default:
		indexAnimIn = 0;
		indexAnimOut = 1;
	}
}

void Animator::DrawSkeleton(Body* body, int curFrame)
{
	for (int i = 1; i < body->GetBonesCount(); i++)
	{
		maths::Vec3 posBone = finalPosition[i];
		maths::Vec3 posBoneParent = finalPosition[body->GetBone(i)->GetParentIndex()];

		if (body->GetBone(i)->GetParentIndex() != 0)
			DrawLine(posBone.x + 50, posBone.y - 50, posBone.z, posBoneParent.x + 50, posBoneParent.y - 50, posBoneParent.z, color.x, color.y, color.z);
	}
}