#pragma once
#include"SubWeapon.h"
#include "Hit.h"
#include"Gate.h"
#include"Ground.h"
#define knife_ani 0
#define knife_ani_set 6

#define SCREEN_WIDTH 530
#define SCREEN_HEIGHT 500
#define knife_box_width 34
#define knife_box_height 18

#define knife_vx 0.35
#define add_dis_max 100
class Knife :public SubWeapon
{
	
public:
	Knife();
	~Knife();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void collisionwith(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void aabbmob(vector<LPGAMEOBJECT>* listmob);
	void SetV();
	void SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding);
	bool CheckPosKnife(float a);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

