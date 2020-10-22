#pragma once
#include"Animation.h"
#include"Sprites.h"
#define simon_heal 0
#define lose_heal 1
#define boss_heal 2
#define healthbar_ani_set 9

#define max_heal 16
class HealthBar
{
	//LPANIMATION healthbar;
	vector<LPANIMATION_SET> healthbar;
	float posx, posy;
	int currenthealth, maxhealth;
	bool healthsimon;
	//vector<LPANIMATION> bar;
public:
	HealthBar(int heal);
	~HealthBar();
	void Update(int currenthealth/*,float x, float y*/);
	void Render(int state,int camx,int camy);
};

