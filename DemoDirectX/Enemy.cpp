#include "Enemy.h"

Enemy::Enemy()
{

}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject,bool clk)
{
	CGameObject::Update(dt);
}

void Enemy::SetState(int State)
{
	CGameObject::SetState(State);
}

int Enemy::getHp()
{
	return CGameObject::getHp();
}

void Enemy::loseHp(int x)
{
	hp -= x;
	if (hp <= 0)
		hp = 0;
}
Enemy::~Enemy()
{
}
