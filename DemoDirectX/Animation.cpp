#include "Animation.h"
#include "Utils.h"

CAnimationSets * CAnimationSets::__instance = NULL;

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(int nx, float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}

	frames[currentFrame]->GetSprite()->Draw(nx, x, y, alpha);
}

void CAnimation::RenderWhip(int currentID, int nx, float x, float y, int alpha)
{
	//currentFrame = currentID;
	frames[currentID]->GetSprite()->Draw(nx, x, y, alpha);
}



CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}


void CAnimations::Clear(int id)
{
	LPANIMATION ani = animations[id];
	delete ani;

	animations.erase(id);
}

CAnimationSets::CAnimationSets()
{
}

CAnimationSets *CAnimationSets::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimationSets();
	return __instance;
}

LPANIMATION_SET CAnimationSets::Get(unsigned int id)
{
	LPANIMATION_SET ani_set = animation_sets[id];
	if (ani_set == NULL)
		DebugOut(L"[ERROR] Failed to find animation set id: %d\n", id);

	return ani_set;
}

void CAnimationSets::Clear(unsigned int id)
{
	LPANIMATION_SET aniset = animation_sets[id];
	delete aniset;

	animation_sets.erase(id);
}

void CAnimationSets::Add(int id, LPANIMATION_SET ani_set)
{
	animation_sets[id] = ani_set;
}