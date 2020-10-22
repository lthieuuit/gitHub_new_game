#pragma once
#include"GameObject.h"
#include"Hit.h"
#include"Knight.h"
#include"Bat.h"
#include"Skeleton.h"
#include"Raven.h"
#include"Monkey.h"
#include"BreakWall.h"
#include"SmallCandle.h"
#include"Frog.h"
#include"Zombie.h"
#include"Boss.h"
#define whip_lv1 0
#define whip_lv2 1
#define whip_lv3 2

#define whip_ani_set 4

#define whip_box_width_lv12 55
#define whip_box_width_lv3 85
#define whip_box_height 15

#define whip_dame1 1
#define whip_dame2 2

#define pos_whip_x 90
#define pos_whip_y 15

#define pos_whip_lv3 20
#define pos_whip_lv1_2 50
#define pos_whip_lv3_2_1_left 135

class Whip :public CGameObject
{
	
	bool delaydamage;
public:
	vector<LPHIT> listHit;
	Whip();
	~Whip();
	Hit* CreateHit(float x, float y);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render(int currentID = -1);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetPosWhip(D3DXVECTOR3 pos, bool isstanding);
	void Setdelaydamage(bool a) { delaydamage = a; }
	bool WhipCheckColli(float l_b, float t_b, float r_b, float b_b);
	void SetLvWhip(int state)
	{
		this->state = state;
	}
	
};

