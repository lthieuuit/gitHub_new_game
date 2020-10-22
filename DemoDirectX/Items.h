#pragma once
#include"GameObject.h"
#include"Ground.h"
#include"BreakWall.h"
#define time_items_des 4500
#define items_for_whip 0
#define items_big_heart 1
#define items_knife 2
#define items_watch 3
#define items_axe 4
#define items_boom 5
#define items_holywater 6
#define items_watterbottle 7
#define items_corss 8
#define items_double 9
#define items_triple 10
#define items_meat 11
#define items_small_heart 12
#define items_bluemoney 13
#define items_redmoney 14
#define items_whitemoney 15
#define items_crown 16
#define items_boss 17

#define small_heart_vx 0.005
#define items_ani_set 5
#define crown_hight 400
#define crown_appear_vy 0.03

#define items_boss_box_width 26
#define items_boss_box_height 32

#define items_whip_box_width 32
#define items_whip_box_height 32
#define items_bigheart_box_width 24
#define items_bigheart_box_height 20
#define items_knife_box_width 32
#define items_knife_box_height 18
#define items_watch_box_width 30
#define items_watch_box_height 32
#define items_crown_box_width 32
#define items_crown_box_height 32
#define items_money_box_width 30
#define items_money_box_height 30
#define items_smallheart_box_width 16
#define items_smallheart_box_height 16
#define items_double_box_width 28
#define items_double_box_height 28
#define items_triple_box_width 28
#define items_triple_box_height 28
#define items_cross_box_width 32
#define items_cross_box_height 32
#define items_meat_box_width 32
#define items_meat_box_height 26
#define items_axe_box_width 30
#define items_axe_box_height 28
#define items_boom_box_width 30
#define items_boom_box_height 28
#define items_holy_box_width 32
#define items_holy_box_height 28
#define items_water_box_width 29
#define items_water_box_height 33

#define items_vx 0
#define items_vy 0.15

#define value_big_heart 5
#define value_small_heart 1
#define value_meat 4
#define value_bluemoney 500
#define value_redmoney 1000
#define value_whitemoney 1500
#define value_crown 2000


class Items :public CGameObject
{
	DWORD timeStart;
	

public:
	
	Items();
	~Items();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, bool clk = false);
	void Render();
	void SetState(int SetState);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};

