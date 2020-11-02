#pragma once
#include "GameObject.h"
#include "Simon.h"

#define WEAPON_STATE_HIDDEN 0
#define WEAPON_STATE_ATTACK 1

#define WEAPON_ATTACK_TIME 500
#define WEAPON_X 10
#define WEAPON_Y 15

#define WEAPON_ANI_1	0
#define WEAPON_ANI_2	1
#define WEAPON_ANI_3	2

#define WEAPON_WIDHT_ANI_1	44;
#define WEAPON_HEGTH_ANI_1	23;


class CWeapon : public CGameObject
{
	static CWeapon* __instance;
	int level;
	int frame;
	int width = 0;
	int heigth = 0;
	DWORD action_time;


public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);

	void ResetAnimation();
	void SetFrame(int _frame) { frame = _frame; };
	int GetFrame() { return frame; };
	void UpdatePosionWithSimon(float _x, float _y, int _nx);
	static CWeapon* GetInstance();
	CWeapon();
	~CWeapon();

	void SetLevel(int _level) { level = _level; };
	int GetLevel() { return level; };
	
	int GetAnimation();
	void GetPositionForSimon();
};