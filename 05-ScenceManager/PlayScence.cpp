#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Map.h"
#include "Board.h"
#include"BlackLeopard.h"
#include"Zombie.h"
#include "Item.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

void CPlayScene::Load()
{
	LoadObject();
	LoadMap();
}

void CPlayScene::LoadMap() {
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	tilemap = new TileMap();
	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];

	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;
		if (line == "[SCENEOBJECT]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_LOADMAP; continue;
		}
		

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
		case SCENE_SECTION_OBJECTS: _ParseSection_SCENEOBJECT(line); break;
		case SCENE_SECTION_LOADMAP: _ParseSection_INFOMAP(line); break;
		}
	}
	f.close();
}

void CPlayScene::_ParseSection_SCENEOBJECT(string file) {
	ifstream f;
	f.open(file);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;// skip comment lines
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", file);
}
void CPlayScene::LoadObject() {
	ifstream f;
	f.open(L"Scenes\\Castlevania.txt");

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;// skip comment lines
		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::_ParseSection_LOADMAP(string line)
{
	vector<string> tokens = split(line);

	//test set id
	int r, l, id = 400;

	if (tokens.size() < 4) return; // skip invalid lines
	if (atoi(tokens[0].c_str()) == 0)
	{
		//load intro map sate = 0
		isintro = 1;
		int texID = atoi(tokens[3].c_str());
		LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
		if (tex == NULL)
		{
			DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
			return;
		}
		CSprites::GetInstance()->Add(400, 0, 0, 448, 512, tex);
		LPANIMATION ani = new CAnimation(100);	// idle big right
		//add ani;
		ani->Add(id);
		CAnimations::GetInstance()->Add( id, ani);
		///set ani to obj
		LPANIMATION_SET s = new CAnimationSet();
		CAnimations * animations = CAnimations::GetInstance();
		s->push_back(animations->Get(0));
		CAnimationSets::GetInstance()->Add(400, s);
		map->SetState(0);
	}
	else
	{
		int IDMap = atoi(tokens[0].c_str());
		wstring path = ToWSTR(tokens[1]);
		int frame = atoi(tokens[2].c_str());
		int texID = atoi(tokens[3].c_str());
		//int B = atoi(tokens[4].c_str());
		LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
		if (tex == NULL)
		{
			DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
			return;
		}
		//int frame = 49;//114;
		for (int i = 0; i < frame; i++)
		{
			if (i == 0)
			{
				r = 32;
				l = 0;
			}
			else
			{

				l = i * 32;
				r = l + 32;
			}
			//auto add id sprite
			CSprites::GetInstance()->Add(i + id, l, 0, r, 32, tex);
			LPANIMATION ani = new CAnimation(100);	// idle big right
			//add ani;
			ani->Add(i + id);
			CAnimations::GetInstance()->Add(i + id, ani);
		}
		map = new CMap();
		map->ReadMap(IDMap, path.c_str());
		map->SetState(IDMap);
		isintro = 0;
		LPANIMATION_SET s = new CAnimationSet();

		CAnimations* animations = CAnimations::GetInstance();

		for (int i = 0; i < map->col + 1; i++)
		{
			LPANIMATION ani = animations->Get(400 + i);
			s->push_back(ani);
			CAnimationSets::GetInstance()->Add(i + 4000, s);
		}
	}
}

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	int id = 0;

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] simon object was created before!\n");
			return;
		}
		obj = new CSimon(x,y); 
		player = (CSimon*)obj;
		if (isintro == 1) 
		{ 
			player->SetNX(0); 
			player->SetState(SIMON_STATE_WALKING);
		}
		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_BLACK_LEOPARD: obj = new CBlackLeopard(); break;
	case OBJECT_TYPE_ZOMBIE: obj = new CZombie(); break;
	case OBJECT_TYPE_WEAPON: 
		obj = new CWeapon(); 
		weapon = (CWeapon*)obj;
		break;
	case OBJECT_TYPE_AXE:
		obj = new CAxe();
		this->axe = (CAxe*)obj;
		break;
	case OBJECT_TYPE_KOOPAS: obj = new CKoopas(); break;
	case OBJECT_TYPE_BOARD: 
		obj = new CBoard();
		board = (CBoard*)obj;
		break;
	case OBJECT_TYPE_PORTAL:
		{	
			float r = atof(tokens[4].c_str());
			float b = atof(tokens[5].c_str());
			int scene_id = atoi(tokens[6].c_str());
			obj = new CPortal(x, y, r, b, scene_id);
		}
		break;
	case OBJECT_TYPE_ITEM:
		id = atof(tokens[4].c_str());
		obj = new CItem();
		item = (CItem*)obj;
		if (id == ID_ITEM_TYPE_TORCH) {
			item->SetID(ITEM_ANI_TORCH);
		}else if (id == ID_ITEM_TYPE_CANDLE) {
			item->SetID(ITEM_ANI_CANDLE);
		}
		else {
			item->SetID(0);
		}

		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::_ParseSection_INFOMAP(string line)
{
		vector<string> tokens = split(line);
		if (tokens.size() < 10) return;
		int IDmap = atoi(tokens[0].c_str());
		wstring pathpic = ToWSTR(tokens[1]);
		wstring pathtxt = ToWSTR(tokens[2]);
		int num_row = atoi(tokens[3].c_str());
		int num_col = atoi(tokens[4].c_str());
		int num_row_read = atoi(tokens[5].c_str());
		int num_col_read = atoi(tokens[6].c_str());
		int tile_width = atoi(tokens[7].c_str());
		int tile_height = atoi(tokens[8].c_str());
		idstage = atoi(tokens[9].c_str());
		int r = atoi(tokens[14].c_str());
		int g = atoi(tokens[15].c_str());
		int b = atoi(tokens[16].c_str());

		tilemap->LoadMap(IDmap, pathpic.c_str(), pathtxt.c_str(), num_row, num_col, num_row_read, num_col_read, tile_width, tile_height, r, g, b);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that simon is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	
	if (player == NULL) return;

	//update position for simon
	weapon->UpdatePosionWithSimon(player->GetPositionX(), player->GetPositionY(), player->nx);
	// Update camera to follow mario
	CGame* game = CGame::GetInstance();
	float cx, cy;
	player->GetPosition(cx, cy);
	
	
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	
	// fix bug camera 
	if (cx < 0) {
		cx = 0.0f;
	}
	board->SetPosition(cx - (game->GetScreenWidth() / 2), 0);
	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
}

void CPlayScene::Render()
{
	tilemap->Draw();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

bool CPlayScene::CheckInCam(LPGAMEOBJECT a)
{
	CGame* game = CGame::GetInstance();
	return (a->GetPositionX() >= game->GetCamPosX()) && (a->GetPositionX() < (game->GetCamPosX() + SCREEN_WIDTH)) && (a->GetPositionY() >= game->GetCamPosY()) && (a->GetPositionY() < game->GetCamPosY() + SCREEN_HEIGHT);

}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CSimon *simon = ((CPlayScene*)scence)->player;

	if (simon->GetState() == SIMON_STATE_DIE) return;
	// disable control key when simon die
	if (simon->isAttack) return;
	if (game->IsKeyDown(DIK_RIGHT)) Run(1);
	else if (game->IsKeyDown(DIK_LEFT)) Run(-1);
	else simon->SetState(SIMON_STATE_IDLE);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = ((CPlayScene*)scence)->player;
	CPlayScene* playscene = ((CPlayScene*)scence);
	switch (KeyCode)
	{
	case DIK_SPACE: 
		Jump();
		break;
	case DIK_DOWN:
		SitDown();
		break;
	case DIK_X:
		Hit();
		break;
	case DIK_C:
		ThrowSubWeapon();
		break;
	case DIK_A:
		simon->Reset();
		break;
	}
}


void CPlayScenceKeyHandler::Run(int _nx) {
	CSimon* simon = ((CPlayScene*)scence)->player;
	simon->SetNX(_nx);
	simon->SetState(SIMON_STATE_WALKING);
}

void CPlayScenceKeyHandler::Jump() {
	CSimon* simon = ((CPlayScene*)scence)->player;
	DebugOut(L"isGrounded %d \n", simon->isGrounded);
	if (simon->isGrounded) {
		simon->SetState(SIMON_STATE_JUMP);
	}
}

void CPlayScenceKeyHandler::SitDown() {
	CSimon* simon = ((CPlayScene*)scence)->player;
	simon->SetState(SIMON_STATE_SIT_DOWN);
}

void CPlayScenceKeyHandler::Hit() {
	CSimon* simon = ((CPlayScene*)scence)->player;
	CWeapon* weapon = ((CPlayScene*)scence)->weapon;
	weapon->SetState(WEAPON_STATE_ATTACK);
	simon->SetState(SIMON_STATE_HIT);
}

void CPlayScenceKeyHandler::ThrowSubWeapon() {
	CSimon* simon = ((CPlayScene*)scence)->player;
	CAxe* axe = ((CPlayScene*)scence)->axe;
	simon->SetState(SIMON_STATE_HIT);
	axe->UpdatePosionWithSimon(simon->GetPositionX(), simon->GetPositionY(), simon->nx);
	axe->SetState(AXE_STATE_ATTACK);
}