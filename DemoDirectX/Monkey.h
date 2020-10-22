#pragma once
#include"Enemy.h"
#include"Game.h"
#include"Frog.h"
#include"Ground.h"
#define monkey_ani_run 0
#define monkey_ani_die 1
#define monkey_time 300
#define monkey_hp 1
#define monkey_damage 3
#define monkey_score 500
#define monkey_box_width 32
#define monkey_box_height 32
#define monkey_vx_jump 0.1
#define monkey_vx_notjump 0.16
#define monkey_vy -0.4
#define monekey_gra 0.002
#define rand_max 10000
#define rand_min 350
#define dis_si_monkey 150
#define allow_y_jump 330

#define small_dis 100
class Monkey :public Enemy
{
	LPGAMEOBJECT simon;
	bool active, jump; //runfar, check;
public:
	//DWORD timerunfar;
	Monkey(LPGAMEOBJECT simon);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL,bool clk=false);
	void Render();
	void SetState(int State);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void loseHp(int x);
	int getHp();
	bool CheckCam();
	~Monkey();
};

