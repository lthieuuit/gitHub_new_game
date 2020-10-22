#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animation.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	float dx, dy;
	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0,LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny; 
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;

	int state;

	int idItems;
	bool isDone;
	bool isFire;
	int stairdir;

	int nextscene;
	int hp ;

	bool checkoncam;

	DWORD dt;

	//vector<LPANIMATION> animations;
	LPANIMATION_SET animation_set;


	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	float GetPositionX() { return this->x; }
	float GetPositionY() { return this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void SetNx(int nx)
	{
		this->nx = nx;
	}
	int Getnx()
	{
		return nx;
	}
	void SetVx(int vx)
	{
		this->vx = vx;
	}
	virtual int getHp() { return hp; }

	int GetState() { return this->state; }

	void RenderBoundingBox();
	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	bool AABBCheck(float l_a, float t_a, float r_a, float b_a, float l_b, float t_b, float r_b, float b_b);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(    //bộ lọc va chạm
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	//void AddAnimation(int aniId);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL,bool clk=false);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }


	~CGameObject();
};


