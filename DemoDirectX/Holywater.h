#pragma once
#include"SubWeapon.h"
#define holy_vy -0.1
#define holy_vx_right 0.3
#define holy_vx_left -0.25
#define holy_gra 0.001
#define holy_box_width 32
#define holy_box_height 28

#define holy_ani_not_break 0
#define holy_ani_break 1
#define time_fire 1500
#define holy_aniset 22
#define add_dis_hit 10

class Holywater :public SubWeapon
{
	bool isHolyWaterShattered,checkdamage1;
	int holyWaterShatteredCounter;
public:
	Holywater();
	~Holywater();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void collisionwith(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void aabbmob(vector<LPGAMEOBJECT>* listmob);
	void SetV();
	void SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding);
	bool CheckPosKnife(float a);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void StartHolyWater();
	void SetState(int State);

};

