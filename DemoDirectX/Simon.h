#pragma once

#include "GameObject.h"
#include "Whip.h"
#include "Items.h"
#include "SubWeapon.h"
#include "GroundMoving.h"
#include "Knife.h"
#include "Axe.h"
#include "Boomerang.h"
#include "Holywater.h"
#include "Gate.h"
#include "Stair.h"
#include "Knight.h"
#include "Bat.h"
#include "Monkey.h"
#include "Skeleton.h"
#include "Frog.h"
#include "Raven.h"
#include "Zombie.h"
#include "Timer.h"
#include "Boss.h"
#include "Clock.h"

#define simon_jump -0.5f
#define simon_run 0.15f
#define simon_gravity 0.0015f
#define max_screen_left -11
#define simon_ani_idle 0
#define simon_ani_run  1
#define simon_ani_jump 2
#define simon_ani_sit  3
#define simon_ani_stand_hit 4
#define simon_ani_sit_hit   5
#define simon_ani_led 6
#define simon_ani_stair_up 7
#define simon_ani_stair_down 8
#define simon_ani_stair_up_hit 9
#define simon_ani_stair_down_hit 10
#define simon_ani_hurt 11
#define simon_ani_dead 12

#define simon_stair 0.079

#define simon_ani_set 1

#define simon_max_health 16

#define simon_box_width 30
#define simon_box_height 62

#define simon_delay_hit 300
#define simon_delay_led 600

#define simon_delay_hurt 600
#define simon_delay_stair 200

#define sub_distance_down 18
#define sub_distance_up 32

#define simon_alpha_base 255
#define simon_one_second 1000
#define simon_two_second 2500
#define simon_alpha_one_second 70
#define simon_alpha_one_to_two_second 76
#define simon_alpha_random_one_to_two_second 100
#define simon_alpha_random_more_two_second 155
#define box_simon_add 15

#define max_screen_right 1460

#define simon_score 0
#define simon_mana 99
#define simon_life 3
#define simon_t_st 50
#define simon_b_st 10
#define simon_r_st 15
#define simon_stari_down_y 0.5f
#define max_distance -999999
#define simon_nextscene 99
#define simon_hurt_vy -0.3
#define simon_hurt_vx 0.1
#define simon_dead_vy 1000
#define simon_untouchtime 1500
#define simon_watertime 4000
#define max_sub 3
#define mana_use 5
class Simon :public CGameObject
{
	Whip *whip;

	vector<SubWeapon*> listsub;

	SubWeapon *knife[max_sub];
	SubWeapon *axe[max_sub];
	SubWeapon *boom[max_sub];
	SubWeapon *holywater[max_sub];

	SubWeapon *clk;

	int health;
	int score;
	int mana;
	int life;

	
public:

	Timer* untouchtime = new Timer(simon_untouchtime);
	Timer* watertime = new Timer(simon_watertime);
	bool checkgroundmove=false;
	bool isCross;
	bool isDead;

	

	bool bossdie;

	int hitDoubleTriple = -1;
	int currentscene;
	int beforescene;

	float newPosX;
	int stateAfterAutoWalk = -1;	
	int nxAfterAutoWalk;

	bool StairLeftFirst;

	bool isWalkStair;
	bool isStandOnStair;
	bool canmoveupstair;
	bool canmovedownstair;
	int stairNx;

	LPGAMEOBJECT stairCollided;

	bool isGrounded;
	bool isHitSubWeapon;
	bool isChangeScene;
	int currentWeapon;
	//bool batdie;
	//bool ravendie;
	Simon();
	~Simon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, bool clk = false);
	void Render();
	void SetState(int SetState);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Whip* GetWhip()
	{
		return whip;
	}
	vector<SubWeapon*> GetListSubWeapon() { return listsub; }
	int getcurrentweapon() { return currentWeapon; }
	int getscore() { return score; }
	int getmana() { return mana; }
	int getlife() { return life; }

	void InstallKnife();
	void InstallAxe();
	void InstallBoom();
	void InstallHoly();
	void InstallClk();
	
	void usemana(int a) { mana -= a; }
	void SimonColliWithItems(vector<LPGAMEOBJECT> *listitems);
	bool SimonColliWithStair(vector<LPGAMEOBJECT> *liststair);
	void SimonColliWithMob(vector<LPGAMEOBJECT> *listmob);
	void StandOnStair();
	void AutoWalkStair(float newPosX, int stateAfterAutoWalk, int nxAfterAutoWalk);
	void DoAutoWalkStair();
	void loseHp(int x);
	void setHealth(int a) { health = a; }
	void setMana(int a) { mana = a; }
	void setScore(int a) { score = a;}
	void setLife(int a) { life = a; }
	void addScore(int a) { score += a; }
	int GetHealth() { return health; }
	void addHp(int a) {
		health += a;
		if (health >= simon_max_health)
			health = simon_max_health;
	}
};

