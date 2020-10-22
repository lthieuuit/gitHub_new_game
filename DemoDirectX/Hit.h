#pragma once
#include"Animation.h"
#include"Sprites.h"
#define hit_ani 0//91
#define hit_ani_set 7
#define time_hit_des 100

#define hit_sprite 113
class Hit;
typedef Hit* LPHIT;

class Hit
{
	DWORD timestart=-1;
	float x, y;
	//LPANIMATION hit;
	LPANIMATION_SET hit;
	//LPSPRITE hit;
public:
	
	Hit(float x, float y);
	~Hit();
	void Render();
	bool timedestroy();
};

