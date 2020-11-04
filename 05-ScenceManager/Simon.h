#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_ATTACK_TIME 500

#define SIMON_STATE_IDLE				0
#define SIMON_STATE_WALKING				1001
#define SIMON_STATE_JUMP				1002
#define SIMON_STATE_SIT_DOWN			1003
#define SIMON_STATE_HIT					1004
#define SIMON_STATE_SIT_HIT				1005
#define SIMON_STATE_STAIR_UP			1006
#define SIMON_STATE_STAIR_DOWN			1007
#define SIMON_STATE_STAIR_UP_HIT		1008
#define SIMON_STATE_STAIR_DOWN_HIT		1009
#define SIMON_STATE_STAIR_HURT			1010
#define SIMON_STATE_DIE					1011

#define SIMON_ANI_IDLE				0
#define SIMON_ANI_WALKING			1
#define SIMON_ANI_JUMP				2
#define SIMON_ANI_SIT_DOWN			3
#define SIMON_ANI_STAND_HIT			4
#define SIMON_ANI_SIT_HIT			5
#define SIMON_ANI_LED				6
#define SIMON_ANI_STAIR_UP			7
#define SIMON_ANI_STAIR_DOWN		8
#define SIMON_ANI_STAIR_UP_HIT		9
#define SIMON_ANI_STAIR_DOWN_HIT	10
#define SIMON_ANI_STAIR_HURT		11
#define SIMON_ANI_DIE				12
#define SIMON_ANI_WHIP_LV1			13
#define SIMON_ANI_WHIP_LV2			14
#define SIMON_ANI_WHIP_LV4			15

#define SIMON_HEGHT					60
#define SIMON_WIDTH					30

#define SIMON_HEGHT_RESET_SIT		17

#define SIMON_WIDTH_RESET_ATTACK	7

#define SIMON_ANI_DIE				8

#define	SIMON_LEVEL_SMALL			1
#define	SIMON_LEVEL_BIG				2

#define SIMON_UNTOUCHABLE_TIME		5000
#define SIMON_RESET_JUMP_TIME		500


class CSimon : public CGameObject
{
public:
	int level;
	int untouchable;
	int height = 65;
	int width = 34;
	bool isSit;
	bool isAttack;
	bool isGrounded;
	int actionAttack = 0;	// 0 right 1 left

	int start_x;
	int start_y;

	DWORD untouchable_start;
	DWORD action_time;
public:
	CSimon();
	virtual void SitDown();
	virtual void attack();
	virtual void ResetAnimation();
	virtual void Reset();
	CSimon(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void Render();
	void SetNX(int _nx) { nx = _nx; }
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	bool GetAttack() { return this->isAttack; };

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};