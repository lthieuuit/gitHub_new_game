#pragma once
#include "GameObject.h"

#define WEAPON_STATE_HIDDEN 0
#define WEAPON_STATE_ATTACK 1

#define WEAPON_ATTACK_TIME 500
#define WEAPON_X 10
#define WEAPON_Y 15

#define WEAPON_ANI_1_RIGHT	0
#define WEAPON_ANI_2_RIGHT	1
#define WEAPON_ANI_3_RIGHT	2

#define WEAPON_ANI_1_LEFT	3
#define WEAPON_ANI_2_LEFT	4
#define WEAPON_ANI_3_LEFT	5

class CWeapon : public CGameObject
{
	static CWeapon* __instance;
	int level;
	int frame;
	DWORD action_time;
	

public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);

	void ResetAttack();
	void SetFrame(int _frame) { frame = _frame; };
	int GetFrame() { return frame; };
	void UpdatePosionWithSimon(int _x, int _y, int _nx);
	static CWeapon* GetInstance();
	CWeapon();

	void SetLevel(int _level) { level = _level; };
	int GetLevel() { return level; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetAnimation();
	void GetPositionForSimon();
	
};
