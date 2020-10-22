#pragma once
#include"Enemy.h"
#include"Game.h"
#include"Timer.h"
#define frog_ani_die 1
#define frog_time 300

#define frog_hp 3
#define frog_damage 3
#define frog_score 300

#define frog_box_width 32
#define frog_box_height 32

#define frog_vx 0.08
#define frog_xy 0.05
#define frog_stop 150
#define dis_back 40
#define dis_appear 200
#define dis_up_down 20
class Frog :public Enemy
{
	LPGAMEOBJECT simon;
public:
	bool check;
	DWORD timestop;
	Frog(LPGAMEOBJECT simon);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL,bool clk=false);
	void Render();
	void SetState(int State);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void loseHp(int x);
	int getHp();
	bool CheckCam();
	~Frog();
};

