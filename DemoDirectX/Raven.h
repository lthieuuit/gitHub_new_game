#pragma once
#include"Enemy.h"
#include"Game.h"
#include"Timer.h"
#define raven_ani_idle 0
#define raven_ani_fly 1
#define raven_ani_die 2
#define raven_time 300

#define raven_hp 1
#define raven_damage 3
#define raven_score 200

#define raven_vx 0.2
#define raven_vy 0.1

#define rand_dis1_min 30
#define rand_dis2_min 40
#define rand_dis_max 400

#define rand_dis3_min 40
#define rand_dis3_max 69

#define rand_dis4_min 30
#define rand_dis4_max 31


#define raven_box_width 32
#define raven_box_height 32

#define wait_time 1800
#define wait1_time 1500
#define dow_time 1500
#define dow1_time 1500
#define stopdown_time 2000
class Raven :public Enemy
{
	LPGAMEOBJECT simon;

	Timer* wait = new Timer(wait_time);
	Timer* wait1 = new Timer(wait1_time);
	Timer* dow = new Timer(dow_time);
	Timer* dow1 = new Timer(dow1_time);
	Timer* timerstopdown = new Timer(stopdown_time);
	bool checkstar,timeflydown,collisimon;
public:
	Raven(LPGAMEOBJECT simon);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL,bool clk=false);
	void Render();
	void SetState(int State);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void loseHp(int x);
	int getHp();
	bool CheckCam();
	void Setcollisimon(bool a) { collisimon = a; }
	bool Getcollisimon() { return collisimon; }
	~Raven();
};

