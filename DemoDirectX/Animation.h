#pragma once
#include"Sprites.h"
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	

	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	DWORD startFrameTime;
	CAnimation(int defaultTime=100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(int nx,float x, float y, int alpha = 255);
	void RenderWhip(int currentID, int nx, float x, float y, int alpha = 255); 
	
	void ResetcurrentFrame()
	{
		currentFrame = -1;
	}

	int GetcurrentFrame()
	{
		return currentFrame;
	}
	void StartAni()
	{
		startFrameTime = GetTickCount();
	}
	bool RenderOver(DWORD a)
	{
		if (GetTickCount() - startFrameTime >= a)
		{
			//startFrameTime = 0;
			return true;
		}
		else
			return false;
	}



};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clear(int id);

	static CAnimations * GetInstance();
};


typedef vector<LPANIMATION> CAnimationSet;

typedef CAnimationSet* LPANIMATION_SET;

/*
	Manage animation set database
*/
class CAnimationSets
{
	static CAnimationSets * __instance;

	unordered_map<int, LPANIMATION_SET> animation_sets;

public:
	CAnimationSets();
	void Add(int id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(unsigned int id);
	void Clear(unsigned int id);

	static CAnimationSets * GetInstance();
};
