#pragma once
#include "GameObject.h"

#define HEIGHT_ID_ANI_0			20
#define WIDTH_ID_ANI_0			23
#define HEIGHT_ID_ANI_1			20
#define WIDTH_ID_ANI_1			23
#define HEIGHT_ID_ANI_2			30
#define WIDTH_ID_ANI_2			30
#define HEIGHT_ID_ANI_3			32
#define WIDTH_ID_ANI_3			26
#define HEIGHT_ID_ANI_4			26
#define WIDTH_ID_ANI_4			32
#define LARGE_HEART_GRAVITY		0.00001f
#define MONEY_BAG_GRAVITY		0.00001f
#define HOLY_WATER_GRAVITY		0.00001f
#define MEAT_GRAVITY			0.00001f

#define ITEM_DISAPPEAR_TIME		5000
#define ITEM_ANI_ROI			0
#define ITEM_ANI_TIM			1
#define ITEM_ANI_MONEY_BAG		2
#define ITEM_ANI_HOLY_WATER		3
#define ITEM_ANI_MEAT			4

class CItem : public CGameObject
{
	int id;
	int height = 0;
	int width = 0;
	DWORD disappearStart;
public:
	CItem();
	~CItem();
	void SetID(int _id) { id = _id; };
	void StartDisappear();
	int GetAnimation();
	void CheckSize();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

