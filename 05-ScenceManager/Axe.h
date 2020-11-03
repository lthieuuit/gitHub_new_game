#pragma once
#include "GameObject.h"
#include "Simon.h"

#define AXE_STATE_HIDDEN 0
#define AXE_STATE_ATTACK 1

#define AXE_ATTACK_TIME 2212
#define AXE_X 10
#define AXE_Y 15
#define AXE_GRAVITY		0.2212f
#define AXE_ANI	0
#define AXE_BBOX_WIDTH 32
#define AXE_BBOX_HEIGHT 32
class CAxe : public CGameObject
{
	static CAxe* __instance;
	int level;
	int frame;
	int vy = 1;
	DWORD action_time;


public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void Render();
	void SetState(int state);

	void ResetAnimation(int ani);
	void SetFrame(int _frame) { frame = _frame; };
	int GetFrame() { return frame; };
	void UpdatePosionWithSimon(int _x, int _y, int _nx);
	static CAxe* GetInstance();
	CAxe();

	void SetLevel(int _level) { level = _level; };
	int GetLevel() { return level; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetAnimation();
	void GetPositionForSimon();

};