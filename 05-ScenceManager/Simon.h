#pragma once
#include "GameObject.h"

class CSimon : public CGameObject
{
public:
	int level;
	int untouchable;
	int height = 60;
	int width = 32;
	bool isSit;
	bool isAttack;
	bool isGrounded;
	int actionAttack = 0;	// 0 right 1 left

	int start_x;
	int start_y;

	DWORD untouchable_start;
public:
	CSimon();
	virtual void SitDown();
	virtual void attack();
	//virtual void ThrowAxe();
	virtual void ResetAnimation();
	virtual void Reset();
	CSimon(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void Render();
	void SetNX(int _nx) { nx = _nx; }
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	//void SetWeapon(CWeapon* _weapon) {
	//	weapon = _weapon;
	//}
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	bool GetAttack() { return this->isAttack; };

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};