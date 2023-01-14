#include "App.h"


App::App()
{
	lerpCrossFade = 0.f;
	speedLerpCrossFade = 0.15f;
	stepAnimationCrossFade = 0;
	matriceArray.clear();

	body = new Body();
	animator = new Animator();

	body->SetBonesCount(GetSkeletonBoneCount() - 6);

	/// SKELETON SETUP ///
	body->RootSetup();
	body->BoneSetup();
	body->ParentSetup();

	/// WORLD T-POSE ///
	for (int i = 0; i < body->GetRootBone()->children.size(); i++)
		body->CalculateWorldBindPose(body->GetRootBone()->children[i]);

	/// ANIMATION SETUP ///
	animations.push_back(new Animation("ThirdPersonWalk.anim", GetAnimKeyCount("ThirdPersonWalk.anim"), body));
	animations.push_back(new Animation("ThirdPersonRun.anim", GetAnimKeyCount("ThirdPersonRun.anim"), body));
	Animation* ownAnim = new Animation(body);
	ownAnim->CreateOwnAnimation();
	animations.push_back(ownAnim);

	float speedAnimOutCrossFade = (float)animations[1]->GetKeyframeCount() * animations[0]->GetSpeed() / (float)animations[0]->GetKeyframeCount();
	animations[1]->SetSpeedAnim(speedAnimOutCrossFade);

	speedAnimOutCrossFade = (float)animations[2]->GetKeyframeCount() * animations[0]->GetSpeed() / (float)animations[0]->GetKeyframeCount();
	animations[2]->SetSpeedAnim(speedAnimOutCrossFade);
}

App::~App() 
{
	for (int i = 0; i < animations.size(); i++)
		delete animations[i];

	delete body;
	delete animator;
}

void App::Update(float deltaTime)
{
	matriceArray.clear();

	UpdateKeyFrame(deltaTime);

	animator->SetAnimInAndOut(stepAnimationCrossFade);
	animator->Animate(matriceArray, body, animations, lerpCrossFade);
	animator->DrawSkeleton(body, animations[0]->GetCurFrame());

	SetSkinningPose(matriceArray.data(), body->GetBonesCount());
}

void App::UpdateKeyFrame(float deltaTime)
{
	for (int i = 0; i < animations.size(); i++)
		animations[i]->UpdateFrame(deltaTime);

	lerpCrossFade += deltaTime * speedLerpCrossFade;

	if (lerpCrossFade > 1.0f)
	{
		lerpCrossFade = 0.f;
		stepAnimationCrossFade++;
		if (stepAnimationCrossFade >= 4)
			stepAnimationCrossFade = 0;
	}
}