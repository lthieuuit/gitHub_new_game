#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Define.h"

#define KNIFE_STATE_HIDDEN 0
#define KNIFE_STATE_ATTACK 1

#define KNIFE_ATTACK_TIME 1400
#define KNIFE_X 10
#define KNIFE_Y 15
#define KNIFE_GRAVITY		0.001f
#define	KNIFE_SPEED_X		0.2512f
#define	KNIFE_SPEED_Y		0.4f
#define KNIFE_ANI	0

class CKnife : public CGameObject
{
	static CKnife* __instance;
	int level;
	int frame;
	int vy = 1;

	DWORD action_time;


public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	//float speedy = KNIFE_SPEED_Y;
	void ResetAnimation(int ani);
	void SetFrame(int _frame) { frame = _frame; };
	int GetFrame() { return frame; };
	void UpdatePosionWithSimon(int _x, int _y, int _nx);
	static CKnife* GetInstance();
	CKnife();

	int knife_isAtk = 1;

	void Attack(DWORD dt);

	void SetLevel(int _level) { level = _level; };
	int GetLevel() { return level; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetAnimation();
	void GetPositionForSimon();

};