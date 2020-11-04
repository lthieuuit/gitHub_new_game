#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Koopas.h"
#include "Map.h"

#include "Brick.h"
#include "Simon.h"
#include "Goomba.h"

#include "Weapon.h"
#include "Axe.h"
#include "Board.h"
#include "Item.h"
#include "Torch.h"
#include "Candle.h"

class CPlayScene: public CScene
{
public: 
	CItem* item;
	CSimon *player;					// A play scene has to have player, right? 
	CMap* map;
	CWeapon* weapon;
	CAxe* axe;
	CBoard* board;
	vector<LPGAMEOBJECT> objects;
	int isintro = 0;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_LOADMAP(string line);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	bool CheckInCam(LPGAMEOBJECT a);

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};

	void Run(int _nx);
	void Jump();
	void Hit();
	void ThrowSubWeapon();

	void SitDown();
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

