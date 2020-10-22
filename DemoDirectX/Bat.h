#pragma once
#include"Enemy.h"
#include"Game.h"
#define bat_box_width 32
#define bat_box_height 32
#define bat_ani_idle 0
#define bat_ani_fly 1
#define bat_ani_die 2
#define bat_time 300
#define SCREEN_WIDTH 530
#define bat_speed 0.2
#define bat_gravity 0.25
#define bat_distance 160
#define bat_distance_max 200
#define bat_distance_min 130
#define simon_ani_stair_down 8
#define simon_ani_stair_up 7
#define simon_ani_jump 2
#define simon_ani_stand_hit 4
#define bat_ani_fly_vy 0.00004
#define bat_hp 1
#define bat_damage 2
#define bat_score 200
class Bat :public Enemy
{
	LPGAMEOBJECT simon;
	bool checkpos,collisimon;//kt xem vị trí dơi đã thấp chưa
public:
	Bat(LPGAMEOBJECT simon);
	~Bat();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL,bool clk=false);
	void Render();
	void SetState(int State);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void loseHp(int x);
	int getHp();
	bool CheckCam();
	void Setcollisimon(bool a) { collisimon = a; }
	bool Getcollisimon() { return collisimon; }
};

