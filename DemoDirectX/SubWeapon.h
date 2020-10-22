#pragma once
#include"GameObject.h"
#include"Candle.h"
#include"Gate.h"
#include"GroundMoving.h"
#include"Knight.h"
#include"Monkey.h"
#include"Frog.h"
#include"Hit.h"
#include"BreakWall.h"
#include"SmallCandle.h"
#include"Skeleton.h"
#include"Raven.h"
#include"Ground.h"
#include"Zombie.h"
#include"Boss.h"

#define weapon_knfie 0
#define weapon_watch 1
#define weapon_axe 2
#define weapon_boom 3
#define weapon_holy 4

#define dame_into_knight 2
#define dame_into_bat 1
#define dame_into_monkey 1
#define dame_into_frog 2
#define dame_into_skele 1
#define dame_into_raven 1
#define dame_into_zombie 1
#define dame_into_boss 2

#define set_pos_sub_nsit 25
#define set_pos_sub_sit 10
#define add_dis_hit 10
class SubWeapon :public CGameObject
{
protected:
	vector<LPHIT> listHit;
	LPGAMEOBJECT simon;
	float POSX;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();

	virtual void SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void collisionwith(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void SetV() = 0;
	void renderlisthit();
	Hit* CreateHit(float x, float y);
	virtual void SetState(int State){}
	SubWeapon();
	SubWeapon(LPGAMEOBJECT simon)
	{
		this->simon = simon;
	}

	void ClearListHit();


	~SubWeapon();
};

