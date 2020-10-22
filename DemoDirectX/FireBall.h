#pragma once
#include"Enemy.h"
#include"Game.h"
#define fireball_box_width 10
#define fireball_box_height 12
#define add_pos_boss 25
#define fireball_damage 1
#define fireball_aniset 888
#define add_cam_x 50
#define add_cam_y 30
#define v_base 0.2
class FireBall :public Enemy
{
public:
	bool checkset;
	float POSX,POSY;
	FireBall();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void setpos(D3DXVECTOR2 pos);
	bool CheckCam();
	void setspeed(float xs, float ys,int nx,int ny);
	~FireBall();
};

