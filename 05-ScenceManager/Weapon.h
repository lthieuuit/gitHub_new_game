#pragma once
#include "GameObject.h"

class CWeapon : public CGameObject
{
public:
	static CWeapon* __instance;
	int level;
	int frame;
	int width = 0;
	int heigth = 0;
	DWORD action_time;


public:
	//int whip_isAtk = 1;

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