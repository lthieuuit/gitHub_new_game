#pragma once
#include"Enemy.h"
#include"Game.h"
#include"Timer.h"
#include"FireBall.h"
#define boss_ani_fly 1
#define boss_ani_die 2
#define boss_time 900

#define boss_max_hp 16
#define boss_damage 2
#define boss_score 3000
#define boss_box_width 70
#define boss_box_height 46
#define boss_active 96
#define max_distance 900
#define rand_min 80
#define screen_box_left 10
#define screen_box_right 420
#define screen_box_up 100
#define screen_box_down 380
#define max_dis_right_left 150
#define max_dis_up_down 100
#define vx_right_left 0.12
#define vy_right_left 0.05
#define vy_donw 0.09
#define add_x 13
#define vx_close 0.12
#define time_attack_stop 2300//1500
class Boss :public Enemy
{
	LPGAMEOBJECT s;
	int ny;
	Timer* timer1 = new Timer(time_attack_stop);
	FireBall* fireball;
public:
	bool checkactive,target,checkstop,fly;
	Boss(LPGAMEOBJECT s);
	~Boss();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool clk = false);
	void Render();
	void SetState(int State);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void loseHp(int x);
	int getHp();
	FireBall* getFireBall() { return fireball; }
	//bool CheckCam();
};

