#pragma once
#include"Enemy.h"
#include"Game.h"
#include"Ground.h"
#define zombie_ani_die 1
#define zombie_ani_run 0
#define zombie_time 300
#define zombie_box_width 28
#define zombie_box_height 64
#define zombie_hp 1
#define zombie_damage 2
#define zombie_score 100
#define zombie_gra 0.02
#define zombie_vx 0.15
class Zombie :public Enemy
{
public:
	bool check, colliwhip;
	Zombie();
	~Zombie();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL, bool clk = false);
	void Render();
	void SetState(int State);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void loseHp(int x);
	int getHp();
	bool CheckCam();
};

