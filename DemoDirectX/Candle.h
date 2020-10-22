#pragma once
#include"GameObject.h"
#define candle_big_ani 0

#define break_candle 1


#define candle_width 32
#define candle_height 64

#define candle_ani_set 3
#define time_render_fire 300
class Candle :public CGameObject
{
public:
	Candle();
	~Candle();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL,bool clk=false);
	void Render();
	void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

