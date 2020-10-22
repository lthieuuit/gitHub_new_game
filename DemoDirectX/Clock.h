#pragma once
#include"SubWeapon.h"
class Clock :public SubWeapon
{
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render() {};
	void SetV() {};
	Clock();
	~Clock();
};

