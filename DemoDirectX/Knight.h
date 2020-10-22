#pragma once
#include"Enemy.h"
#include"Ground.h"
#include"Bat.h"
#include"Utils.h"
#define knight_box_height 63
#define knight_box_width 32
#define knight_speed 0.07
#define knight_ani_run 0
#define knight_ani_die 1
#define knight_ani_die_time 300
#define knight_hp 3
#define knight_damage 2
#define knight_score 400
#define knight_gra 0.00015
#define knight_time_stop 150
#define randommax 10000
#define randommin 100
#define coeventtwo 2
class Knight :public Enemy
{
	bool back;
	
public:
	DWORD timestop;
	Knight();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL,bool clk=false);
	void Render();
	void SetState(int State);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void loseHp(int x);
	int getHp();
	~Knight();
};

