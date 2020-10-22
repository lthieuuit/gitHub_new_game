#pragma once
#include"SubWeapon.h"
#include"Simon.h"
#define boom_aniset 21
#define boom_box_width 28
#define boom_box_height 28
#define boom_vx 0.4
#define boom_comeback_vx 0.006
#define add_dis_cam 0//135
#define add_dis_hit 10
class Boomerang :public SubWeapon
{
	bool checkdamage1;
public:
	Boomerang(LPGAMEOBJECT simon);
	~Boomerang();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void collisionwith(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void aabbmob(vector<LPGAMEOBJECT>* listmob);
	void SetV();
	void SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding);
	bool CheckPosKnife(float a);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

