#pragma once
#include"SubWeapon.h"

#define axe_gra 0.001
#define axe_vx 0.2
#define axe_vy -0.45
#define axe_box_width 30
#define axe_box_height 28
#define axe_max_dis 100
#define axe_ani_set 20

class Axe :public SubWeapon
{
public:
	bool checkdamage1;
	Axe();
	~Axe();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void collisionwith(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void aabbmob(vector<LPGAMEOBJECT>* listmob);
	void SetV();
	void SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding);
	bool CheckPosKnife(float a);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
