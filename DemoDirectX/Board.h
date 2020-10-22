#pragma once
#include"Animation.h"
#include"Sprites.h"
#include"HealthBar.h"
#include"Simon.h"
#include"Number.h"
#include<string>
#include<time.h>

#define board_ani_set 8
#define board_ani 0

#define board_sprite 125

#define max_num_time 4
#define max_num_score 6
#define max_num_mana 2
#define max_num_stage 2
#define max_num_life 2

#define def_time_max 400

#define sprite_knife 82
#define sprite_watch 83
#define sprite_axe 84
#define sprite_boom 85
#define sprite_holy 86
#define sprite_double 202
#define sprite_triple 203
#define add_x_doutriple 440
#define add_y_doutriple 31
#define add_x_sub 312
#define add_x1_sub 310
#define add_y_boom 36
#define add_y_holy_axe 33
#define add_y_watch 29
#define add_y_knife 36
#define add_x_time 295
#define add_y_time 15
#define add_x_score 100
#define add_y_score 15
#define add_x_mana 393
#define add_y_mana 33
#define add_x_stage 465
#define add_y_stage 15
#define add_x_life 393
#define add_y_life 51
class Board
{
	//LPANIMATION board;
	LPANIMATION_SET board;
	//LPSPRITE board;
	//float posx, posy;
	HealthBar *healsimon;
	HealthBar *heallost;
	HealthBar *healboss;
	Number numb;

	string FillNumber(string s, UINT MaxNumber);
	vector<LPSPRITE> subweapon;
	vector<LPSPRITE> doubletriple;

	int time, timeremain;
	int timemax;
	bool checktime;

public:
	Board(int healsimon,int healboss);
	~Board();
	void Update(DWORD dt,int currentheal,int healboss);
	void Render(int idmap, int camx, int camy, Simon* simon);
	bool getCheckTime() {return checktime;}
	void setCheckTime(bool a) { checktime = a; }
	void settimeremain(int a) { timemax = a; time = 0; }
	void settimer(int a) { timeremain = a; }
	int gettimemax() { return timemax; }
	int gettimeremain() { return timeremain; }
	void subtimemax(int a)
	{
		timemax -= a;
		if (timemax <= 0)
			timemax = 0;
	}
};

