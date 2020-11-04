#pragma once
#include "GameObject.h"

#define ITEM_GRAVITY		0.00005f
#define ITEM_TIME_FIRE					1000

#define ITEM_DISAPPEAR_TIME		5000
#define ITEM_ANI_ROI			0
#define ITEM_ANI_TIM			1
#define ITEM_ANI_MONEY_BAG		2
#define ITEM_ANI_HOLY_WATER		3
#define ITEM_ANI_MEAT			4
// item phu
#define ITEM_ANI_TORCH			18
#define ITEM_ANI_CANDLE			19
#define ITEM_ANI_FIRE			20


#define ITEM_HEIGHT_ID_ANI_TORCH		64
#define ITEM_WIDTH_ID_ANI_TORCH			32
#define ITEM_HEIGHT_ID_ANI_CANDLE		15
#define ITEM_WIDTH_ID_ANI_CANDLE		15

#define ITEM_HEIGHT_ID_ANI_0			32
#define ITEM_WIDTH_ID_ANI_0				32
#define ITEM_HEIGHT_ID_ANI_1			20
#define ITEM_WIDTH_ID_ANI_1				24
#define ITEM_HEIGHT_ID_ANI_2			30
#define ITEM_WIDTH_ID_ANI_2				30
#define ITEM_HEIGHT_ID_ANI_3			28
#define ITEM_WIDTH_ID_ANI_3				32
#define ITEM_HEIGHT_ID_ANI_4			26
#define ITEM_WIDTH_ID_ANI_4				32



class CItem : public CGameObject
{
public:
	int id;
	int height = 1;
	int width = 1;
	bool isCandle = false;
	bool isTorch = false;
	bool isFire = false;
public:

	CItem();
	~CItem();
	void SetID(int _id) { id = _id; };
	int GetAnimation();
	void CheckSize();
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
