#pragma once
#include "GameObject.h"

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
