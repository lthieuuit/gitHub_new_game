#pragma once
#include "Game.h"
#include "Utils.h"
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
#include "Knife.h"
#include "Holywater.h"

#include "Board.h"
#include "Item.h"
#include "TileMap.h"

#include "Define.h"

class CPlayScene: public CScene
{
public: 
	CItem* item;
	CSimon *player;					// A play scene has to have player, right? 
	CMap* map;

	CWeapon* weapon;
	CAxe* axe;
	CKnife* knife;
	CHlw* hlw;

	CBoard* board;
	TileMap* tilemap;

	int idstage;
	int current_scene;

	vector<LPGAMEOBJECT> objects;


	vector<string> linkmap;

	int isintro = 0;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_SCENEOBJECT(string line);
	void _ParseSection_INFOMAP(string line);

	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	void _ParseSection_LOADMAP(string line);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void LoadMap();
	void LoadObject();

	bool CheckInCam(LPGAMEOBJECT a);
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};

	int axe_state = 0;

	void Run(int _nx);
	void Jump();
	void Hit();
	void Throw_Axe();
	void Throw_Knife();
	void Throw_Holywater();
	void SitDown();
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

