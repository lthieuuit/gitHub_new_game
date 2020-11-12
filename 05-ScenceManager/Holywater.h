#pragma once
#include "GameObject.h"
#include "Simon.h"

#define HLW_STATE_HIDDEN  0
#define HLW_STATE_ATTACK  1
#define HLW_STATE_COLLIDE 2

#define HLW_ATTACK_TIME 1400
#define HLW_X 10
#define HLW_Y 15
#define HLW_GRAVITY		0.001f
#define	HLW_SPEED_X		0.2212f
#define	HLW_SPEED_Y		0.3f
#define HLW_ANI_ATTACK	0
#define HLW_ANI_COLLIDE	1
class CHlw : public CGameObject
{
	static CHlw* __instance;
	int level;
	int frame;
	int vy = 1;

	DWORD action_time;


public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	float speedy = HLW_SPEED_Y;
	void ResetAnimation(int ani);
	void SetFrame(int _frame) { frame = _frame; };
	int GetFrame() { return frame; };
	void UpdatePosionWithSimon(int _x, int _y, int _nx);
	static CHlw* GetInstance();
	CHlw();

	int hlw_isAtk = 1;

	void Attack(DWORD dt);

	void SetLevel(int _level) { level = _level; };
	int GetLevel() { return level; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetAnimation();
	void GetPositionForSimon();

};