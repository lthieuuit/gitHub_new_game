#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"


#define map1 1
#define map2 2
#define map3 3
#define map4 4
#define map5 5
#define map6 6
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_START	7
#define SCENE_SECTION_LINKMAP	8
#define SCENE_SECTION_SCENEOBJECT	9
#define SCENE_SECTION_INFOMAP	10

#define SCENE_SECTION_CLEARTEXT	11
#define SCENE_SECTION_CLEARSP	12
#define SCENE_SECTION_CLEARANI	13
#define SCENE_SECTION_CLEARANISET	14



#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_GROUND	1
#define OBJECT_TYPE_CANDLE	2
#define OBJECT_TYPE_GATE	3
#define OBJECT_TYPE_STAIR	4
#define OBJECT_TYPE_GROUNDMOVING 5
#define OBJECT_TYPE_KNIGHT 6
#define OBJECT_TYPE_BAT 7
#define OBJECT_TYPE_MONKEY 8
#define OBJECT_TYPE_SKELETON 9
#define OBJECT_TYPE_FROG 10
#define OBJECT_TYPE_DRAVEN 11
#define OBJECT_TYPE_BREAKWALL 12
#define OBJECT_TYPE_SMALLCANDLE 13
#define OBJECT_TYPE_ZOMBIE 14
#define OBJECT_TYPE_BOSS 15


#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


using namespace std;

CPlayScene::CPlayScene() :	CScene()
{
	key_handler = new CPlayScenceKeyHandler(this);
	//sceneFilePath = L"Scenes\\Castlevania.txt";
	Load(L"Scenes\\Castlevania.txt");//load ani sprites texture
	LoadBaseObject();
	SwitchScene(current_scene);

}





void CPlayScene::LoadBaseObject()
{
	if (simon == NULL)
	{
		simon = new Simon();
		DebugOut(L"[INFO]SIMON CREATED \n");
	}
	//boss = new Boss(simon);
	board = new Board(simon->GetHealth(), /*boss->hp*/boss_max_hp);
	tilemap = new TileMap();	
	//grid = new Grid();
	//grididle = new Grid();
}


void CPlayScene::SwitchScene(int idmap)
{
	
	Unload();
	grid = new Grid();
	grididle = new Grid();
	if (simon->beforescene >= 1)
		ClearAll(ToLPCWSTR(linkmap[simon->beforescene-1/*idmap - 2*/]));
	CGame::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
	LPCWSTR a = ToLPCWSTR(linkmap[idmap - 1]);	
	Load(a);
	LoadMap(a);
	LoadObject();
	//grid->PushGrid(listpush);
	//grididle->PushGrid(listidle);
	CGame::GetInstance()->SetCamPos(CGame::GetInstance()->GetCamPosX(), 0.0f);
	simon->currentscene=simon->beforescene = idmap;
}


Items* CPlayScene::DropItem(float x, float y,int id)
{
	Items *a = new Items();

	a->SetPosition(x, y);
	a->idItems = id;
	a->SetState(id);
	
	//listitems.push_back(a);
	return a;
}

void CPlayScene::_ParseSection_CLEARTEXTURES(string line)
{
	vector<string> tokens = split(line);
	for (int i = 0; i < tokens.size(); i++)
		CTextures::GetInstance()->Clear(atoi(tokens[i].c_str()));
}

void CPlayScene::_ParseSection_CLEARSPRITES(string line)
{
	vector<string> tokens = split(line);
	for (int i = 0; i < tokens.size(); i++)
		CSprites::GetInstance()->Clear(atoi(tokens[i].c_str()));
}

void CPlayScene::_ParseSection_CLERANIMATIONS(string line)
{
	vector<string> tokens = split(line);
	for (int i = 0; i < tokens.size(); i++)
		CAnimations::GetInstance()->Clear(atoi(tokens[i].c_str()));
}

void CPlayScene::_ParseSection_CLERANIMATIONSSET(string line)
{
	vector<string> tokens = split(line);
	for (int i = 0; i < tokens.size(); i++)
		CAnimationSets::GetInstance()->Clear(atoi(tokens[i].c_str()));
}

void CPlayScene::_ParseSection_LINKOBJECTS(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 1) return;

	sceneObject= ToLPCWSTR(tokens[0]);
}

void CPlayScene::ClearAll(LPCWSTR a)
{
	ifstream f;
	f.open(a);

	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;

		if (line == "[CLEARTEXT]") {
			section = SCENE_SECTION_CLEARTEXT; continue;
		}
		if (line == "[CLEARSP]") {
			section = SCENE_SECTION_CLEARSP; continue;
		}
		if (line == "[CLEARANI]") {
			section = SCENE_SECTION_CLEARANI; continue;
		}
		if (line == "[CLEARANISET]") {
			section = SCENE_SECTION_CLEARANISET; continue;
		}

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
		case SCENE_SECTION_CLEARTEXT:_ParseSection_CLEARTEXTURES(line); break;
		case SCENE_SECTION_CLEARSP:_ParseSection_CLEARSPRITES(line); break;
		case SCENE_SECTION_CLEARANI:_ParseSection_CLERANIMATIONS(line); break;
		case SCENE_SECTION_CLEARANISET:_ParseSection_CLERANIMATIONSSET(line); break;
		}
	}
	f.close();
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
	if(simon->currentscene<=simon->nextscene)
		CGame::GetInstance()->SetCamPosX(atof(tokens[10].c_str()));
	else
		CGame::GetInstance()->SetCamPosX(atof(tokens[11].c_str()));

	grid->Resize(atoi(tokens[12].c_str()), atoi(tokens[13].c_str()));
	grididle->Resize(atoi(tokens[12].c_str()), atoi(tokens[13].c_str()));
}

void CPlayScene::_ParseSection_LINKMAP(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 1) return;

	linkmap.push_back(tokens[0].c_str());
}

void CPlayScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
		current_scene = atoi(tokens[1].c_str());
	else
		DebugOut(L"[ERROR] Unknown game setting %s\n", ToWSTR(tokens[0]).c_str());
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
		int frame_time = atoi(tokens[i + 1].c_str());
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

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;
	
	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
	{
		int nx1= atof(tokens[3].c_str());
		int state1= atof(tokens[4].c_str());
		float x2= atof(tokens[5].c_str());
		float y2 = atof(tokens[6].c_str());
		int nx2= atof(tokens[7].c_str());
		int state2 = atof(tokens[8].c_str());

		if (simon->currentscene <= simon->nextscene)
		{

			simon->SetNx(nx1);
			simon->SetPosition(x, y);	
			simon->SetState(state1);
		}
		else /*if (simon->currentscene > simon->nextscene)*/
		{
			simon->SetPosition(x2, y2);
			simon->SetNx(nx2);
			simon->SetState(state2);
		}
		
		break;
	}
	case OBJECT_TYPE_GROUND:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new Ground();
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		listidle.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grididle->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_CANDLE: 
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int id = atof(tokens[4].c_str());
		int top = atoi(tokens[5].c_str());
		int bot = atoi(tokens[6].c_str());
		int left = atoi(tokens[7].c_str());
		int right = atoi(tokens[8].c_str());
		obj = new Candle();
		obj->idItems = id;
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		listpush.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_GATE:
	{
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new Gate();
		obj->nextscene = atof(tokens[3].c_str());
		/*current_scene = NEXTMAP;*/
		obj->SetPosition(x, y);
		listidle.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grididle->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_STAIR:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[5].c_str());
		int bot = atoi(tokens[6].c_str());
		int left = atoi(tokens[7].c_str());
		int right = atoi(tokens[8].c_str());
		obj = new Stair();
		int stairnx = atof(tokens[4].c_str());
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		obj->stairdir = stairnx;
		listidle.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grididle->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_GROUNDMOVING:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new GroundMoving();
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		listpush.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_KNIGHT:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new Knight();
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		listpush.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_BAT:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new Bat(simon);
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		listpush.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_MONKEY:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new Monkey(simon);
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		listpush.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_SKELETON:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new Skeleton(simon);
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		listpush.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_FROG:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new Frog(simon);
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		listpush.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_DRAVEN:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new Raven(simon);
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		listpush.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_BREAKWALL:
	{
		int id = atoi(tokens[4].c_str());
		int top = atoi(tokens[5].c_str());
		int bot = atoi(tokens[6].c_str());
		int left = atoi(tokens[7].c_str());
		int right = atoi(tokens[8].c_str());
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj = new BreakWall();
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		obj->idItems = id;
		listpush.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_SMALLCANDLE:
	{
		int id = atoi(tokens[4].c_str());
		int top = atoi(tokens[5].c_str());
		int bot = atoi(tokens[6].c_str());
		int left = atoi(tokens[7].c_str());
		int right = atoi(tokens[8].c_str());
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj = new SmallCandle();
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		obj->idItems = id;
		listpush.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_ZOMBIE:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int nx = atoi(tokens[4].c_str());
		int top = atoi(tokens[5].c_str());
		int bot = atoi(tokens[6].c_str());
		int left = atoi(tokens[7].c_str());
		int right = atoi(tokens[8].c_str());
		obj = new Zombie();
		obj->nx = nx;
		obj->SetAnimationSet(ani_set);
		obj->SetPosition(x, y);
		listpush.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_BOSS:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		boss = new Boss(simon);
		boss->SetAnimationSet(ani_set);
		boss->SetPosition(x, y);
		listpush.push_back(boss);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				grid->PushGridStart(/*obj*/boss, row, col);
		}
		break;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
		break;
	}

}


void CPlayScene::GetObjectGrid()
{
	objects.clear();
	liststairleft.clear();
	liststairright.clear();
	listget.clear();

	grididle->GetGrid(listget);
	grid->GetGrid(listget);
	//DebugOut(L" SO PHAN TU TRONG LIST TĨNH %d \n", listidle.size());
	//DebugOut(L" SO PHAN TU TRONG LIST ĐỘNG %d \n", listpush.size());
	//DebugOut(L" SO PHAN TU TRONG LIST %d \n", listget.size());
	for (UINT i = 0; i < listget.size(); i++)
	{
		if (dynamic_cast<Stair*>(listget[i]))
		{
			if(listget[i]->stairdir==-1)
				liststairright.push_back(listget[i]);
			else
				liststairleft.push_back(listget[i]);
		}
		else
			objects.push_back(listget[i]);
	}
}

void CPlayScene::LoadMap(LPCWSTR map)
{

	ifstream f;
	f.open(map);

	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;

		if (line == "[SCENEOBJECT]") {
			section = SCENE_SECTION_SCENEOBJECT; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_INFOMAP; continue;
		}

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
		case SCENE_SECTION_SCENEOBJECT: _ParseSection_LINKOBJECTS(line); break;
		case SCENE_SECTION_INFOMAP:_ParseSection_INFOMAP(line); break;
		}
	}
	f.close();

}

void CPlayScene::LoadObject()
{

	DebugOut(L"[INFO] StartLOAD OBJECT  resources from : %s \n", sceneObject);

	ifstream f;
	f.open(sceneObject);

	/*if (f.fail())
	{
		DebugOut(L"[ERROR] LOAD OBJECT FAIL : %s \n", sceneObject);
		f.close();
		return;
	}*/

	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;

		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}
	f.close();

	DebugOut(L"[INFO] Done LOAD OBJECT  resources from %s\n", sceneObject);
}

void CPlayScene::Load(LPCWSTR sceneFilePath)
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);


	/*if (f.fail())
	{
		DebugOut(L"[ERROR] LOAD ANISPRITETEXT FAIL : %s \n", sceneFilePath);
		f.close();
		return;
	}*/


	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

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
		if (line == "[SETTINGS]") {
			section = SCENE_SECTION_START; continue;
		}
		if (line == "[LINKMAP]") {
			section = SCENE_SECTION_LINKMAP; continue;
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
		case SCENE_SECTION_START: _ParseSection_SETTINGS(line); break;
		case SCENE_SECTION_LINKMAP:  _ParseSection_LINKMAP(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

int CPlayScene::RandomItems()
{
	int a = rand() % rand_items_max;
	if (min_rand_1 < a &&a <= max_rand_2)
		return items_small_heart;
	else if (max_rand_2 < a && a <= max_rand_3)
		return items_big_heart;
	//else if (max_rand_3 < a&&a <= max_rand_5 && simon->GetWhip()->GetState() < whip_lv3)
		//return items_for_whip;
	else if (max_rand_5 < a &&a <= max_rand_6&&simon->currentWeapon==-1)
		return items_knife;
	else if (max_rand_6 < a&&a <= max_rand_7 && simon->currentWeapon == -1)
		return items_axe;
	else if (max_rand_7 < a&&a <= max_rand_8 && simon->currentWeapon == -1)
		return items_boom;
	else if (max_rand_8 < a &&a <= max_rand_9 && simon->currentWeapon == -1)
		return items_holywater;
	else if (max_rand_9 < a &&a <= max_rand_10)
		return items_watterbottle;
	else if (max_rand_10 < a&&a <= max_rand_11)
		return items_corss;
	else if (max_rand_12 < a &&a <= max_rand_13)
		return items_double;
	else if (max_rand_13 < a&&a <= max_rand_14)
		return items_triple;
	else if (max_rand_14 < a&&a <= max_rand_15)
		return items_meat;
	else if (max_rand_15 < a&&a <= max_rand_16)
		return items_bluemoney;
	else if (max_rand_16 < a&&a <= max_rand_4)
		return items_redmoney;
	else
		return items_whitemoney;
}

bool CPlayScene::CheckInCam(LPGAMEOBJECT a)
{
	CGame* game = CGame::GetInstance();
	return (a->GetPositionX() >= game->GetCamPosX()) && (a->GetPositionX() < (game->GetCamPosX() + SCREEN_WIDTH)) && (a->GetPositionY() >= game->GetCamPosY()) && (a->GetPositionY() < game->GetCamPosY() + SCREEN_HEIGHT);
}

void CPlayScene::UseCross()
{
	if (simon->isCross)
	{
		simon->isCross = false;
		timecross->Start();
		for (UINT i = 0; i < objects.size();i++)
		{
			if (!CheckInCam(objects[i]))
				continue;

			if (dynamic_cast<Knight*>(objects[i]))
			{
				Knight* knight = dynamic_cast<Knight*>(objects[i]);
				knight->SetState(knight_ani_die);
			}
			else if (dynamic_cast<Bat*>(objects[i]))
			{
				Bat* bat = dynamic_cast<Bat*>(objects[i]);
				bat->SetState(bat_ani_die);
			}
			else if (dynamic_cast<Monkey*>(objects[i]))
			{
				Monkey* monkey = dynamic_cast<Monkey*>(objects[i]);
				monkey->SetState(monkey_ani_die);
			}
			else if (dynamic_cast<Frog*>(objects[i]))
			{
				Frog *frog = dynamic_cast<Frog*>(objects[i]);
				frog->SetState(frog_ani_die);
			}
			else if (dynamic_cast<Skeleton*>(objects[i]))
			{
				Skeleton *skele = dynamic_cast<Skeleton*>(objects[i]);
				skele->SetState(skeleton_ani_die);
			}
			else if (dynamic_cast<Raven*>(objects[i]))
			{
				Raven *raven = dynamic_cast<Raven*>(objects[i]);
				raven->SetState(raven_ani_die);
			}
			else if (dynamic_cast<Zombie*>(objects[i]))
			{
				Zombie *zombie = dynamic_cast<Zombie*>(objects[i]);
				zombie->colliwhip = true;
				zombie->SetState(zombie_ani_die);
			}
		}
	}
}


void CPlayScene::ResetGame()
{
	if (simon->bossdie)
	{
		if (!checkreset)
		{
			reset->Start();
			checkreset = true;
		}



		if (simon->GetHealth() < simon_max_health)
		{
			if (delayaddhp->IsTimeUp())
			{
				delayaddhp->Start();
				simon->addHp(1);
			}
		}
		if (simon->getmana() > 0)
		{
			simon->usemana(1);
			simon->addScore(add_score_time_up);
		}

		if (board->gettimemax() > 0)
		{
			board->subtimemax(1);
			simon->addScore(add_score_time);
		}

	}

	if (simon->bossdie&&reset->IsTimeUp())
	{
		reset->Stop();
		simon->bossdie = false;
		board->setCheckTime(false);
		checkreset = false;
		board->settimeremain(def_time_max);
		simon->isDead = false;

		simon->isWalkStair = false;

		simon->GetWhip()->SetState(whip_lv1);
		simon->setHealth(max_heal);
		simon->setMana(simon_mana);
		simon->setLife(simon_life);
		simon->currentWeapon = -1;
		simon->hitDoubleTriple = -1;
		SwitchScene(map1);
		simon->setScore(simon_score);
	}
}



void CPlayScene::Revival()
{
	if (!simon->bossdie)
	{
		CGame* game = CGame::GetInstance();
		if ((simon->GetPositionY() >= (game->GetCamPosY() + SCREEN_HEIGHT/*+ 200*/)))
			simon->SetState(simon_ani_dead);
		if (board->getCheckTime() /*&& !simon->bossdie*/)
		{
			simon->SetState(simon_ani_dead);
			board->setCheckTime(false);
		}

		if ((simon->isDead && timedeadsimon->IsTimeUp()) || (board->getCheckTime() == true))
		{
			timedeadsimon->Stop();

			board->settimeremain(def_time_max);
			simon->isDead = false;
			simon->GetWhip()->SetState(whip_lv1);
			simon->setHealth(max_heal);
			simon->setMana(simon_mana);
			
			simon->isWalkStair = false;


			if (simon->getlife() > 0)
			{
				//board->settimeremain(300);
				simon->setLife(simon->getlife() - 1);
				SwitchScene(simon->currentscene);
			}
			else //if (simon->getlife() == 0)
			{
				simon->setLife(simon_life);
				SwitchScene(map1);
				simon->setScore(simon_score);
			}
		}

		if (simon->GetState() == simon_ani_dead)
		{
			if (!simon->isDead)
			{
				simon->isDead = true;
				timedeadsimon->Start();
			}
		}
	}
	//CGame* game = CGame::GetInstance();
	//if ((simon->GetPositionY() >= (game->GetCamPosY() + SCREEN_HEIGHT /*+ 200*/)))
	//	simon->SetState(simon_ani_dead);
	//if (board->getCheckTime()&&!simon->bossdie)
	//{
	//	simon->SetState(simon_ani_dead);
	//	board->setCheckTime(false);
	//}

	//if ((simon->isDead && timedeadsimon->IsTimeUp()) || (board->getCheckTime() == true))
	//{
	//	timedeadsimon->Stop();

	//	board->settimeremain(def_time_max);
	//	simon->isDead = false;
	//	simon->GetWhip()->SetState(whip_lv1);
	//	simon->setHealth(max_heal);
	//	simon->setMana(simon_mana);
	//	if (simon->getlife() > 0)
	//	{
	//		//board->settimeremain(300);
	//		simon->setLife(simon->getlife() - 1);
	//		SwitchScene(simon->currentscene);
	//	}
	//	else //if (simon->getlife() == 0)
	//	{
	//		simon->setLife(simon_life);
	//		SwitchScene(map1);
	//		simon->setScore(simon_score);
	//	}
	//}

	//if (simon->GetState() == simon_ani_dead)
	//{
	//	if (!simon->isDead)
	//	{
	//		simon->isDead = true;
	//		timedeadsimon->Start();
	//	}
	//}
}

void CPlayScene::Update(DWORD dt)
{
	grid->CheckCamGrid(listpush);
	grididle->CheckCamGrid(listidle);
	GetObjectGrid();

	if (timerclk->IsTimeUp())
		timerclk->Stop();

	if (timecross->IsTimeUp())
		timecross->Stop();
	UseCross();
	vector<LPGAMEOBJECT> coObjects;
	

	
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<Skeleton*>(objects[i]))
		{
			Skeleton* skele = dynamic_cast<Skeleton*>(objects[i]);
			for(int i=0;i< max_bone;i++)
				coObjects.push_back(skele->getBone()[i]);
		}
		if (dynamic_cast<Boss*>(objects[i]))
		{
			Boss *boss = dynamic_cast<Boss*>(objects[i]);
			coObjects.push_back(boss->getFireBall());
		}

		coObjects.push_back(objects[i]);
	}


	for (int i = 0; i < listpiece.size(); i++)
		listpiece[i]->Update(dt);


	if (simon->animation_set->at(simon_ani_stand_hit)->GetcurrentFrame() == 2 && simon->GetState() == simon_ani_stand_hit || (simon->animation_set->at(simon_ani_sit_hit)->GetcurrentFrame() == 2 && simon->GetState() == simon_ani_sit_hit) || (simon->animation_set->at(simon_ani_stair_up_hit)->GetcurrentFrame() == 2 && simon->GetState() == simon_ani_stair_up_hit)|| (simon->animation_set->at(simon_ani_stair_down_hit)->GetcurrentFrame() == 2 && simon->GetState() == simon_ani_stair_down_hit))
	{
		
		if(!simon->isHitSubWeapon)
			simon->GetWhip()->Update(dt, &objects);

	}
	

	for (int i = 0; i < simon->GetWhip()->listHit.size(); i++)
	{
		if (simon->GetWhip()->listHit[i]->timedestroy())
			simon->GetWhip()->listHit.erase(simon->GetWhip()->listHit.begin() + i);
	}
	//DebugOut(L" SO PHAN TU TRONG LISTHIT %d \n", simon->GetWhip()->listHit.size());

	for (UINT i = 0; i < objects.size(); i++)
	{
		LPGAMEOBJECT obj = objects[i]/*allobject[i]*/;
		
		


		if (dynamic_cast<Candle*>(obj) && obj->GetState() == break_candle && !(obj->isDone)&&!(obj->isFire))
		{
			
			if (obj->animation_set->at(break_candle)->RenderOver(time_render_fire))//để khi render xong lửa thì mới rới đồ
			{
				obj->isFire = true;
				listitems.push_back(DropItem(obj->GetPositionX(), obj->GetPositionY(), obj->idItems));
			}
			
		}

		if (dynamic_cast<Knight*>(obj) && obj->GetState() == knight_ani_die && !(obj->isDone) && !(obj->isFire))
		{
			if (obj->animation_set->at(knight_ani_die)->RenderOver(knight_ani_die_time))
			{
				Knight* e = dynamic_cast<Knight*>(obj);
				simon->addScore(e->getScore());
				obj->isFire = true;
				listitems.push_back(DropItem(obj->GetPositionX(), obj->GetPositionY(), RandomItems()));
			}
		}

		if (dynamic_cast<Bat*>(obj) && obj->GetState() == bat_ani_die && !(obj->isDone) && !(obj->isFire))
		{
			if (obj->animation_set->at(bat_ani_die)->RenderOver(bat_time))
			{
				Bat* e = dynamic_cast<Bat*>(obj);

				e->isFire = true;
				if (!e->Getcollisimon())
				{
					simon->addScore(e->getScore());
					listitems.push_back(DropItem(obj->GetPositionX(), obj->GetPositionY(), RandomItems()));
				}
				/*simon->batdie = false;*/
				e->Setcollisimon(false);
			}
		}
		
		if(dynamic_cast<Frog*>(obj) && obj->GetState() == frog_ani_die && !(obj->isDone) && !(obj->isFire))
		{
			if (obj->animation_set->at(frog_ani_die)->RenderOver(frog_time))
			{
				Frog* e = dynamic_cast<Frog *>(obj);
				simon->addScore(e->getScore());
				obj->isFire = true;
				listitems.push_back(DropItem(obj->GetPositionX(), obj->GetPositionY(), RandomItems()));
			}
		}

		if (dynamic_cast<Monkey*>(obj) && obj->GetState() == monkey_ani_die && !(obj->isDone) && !(obj->isFire))
		{
			if (obj->animation_set->at(monkey_ani_die)->RenderOver(monkey_time))
			{
				Monkey* e = dynamic_cast<Monkey *>(obj);
				simon->addScore(e->getScore());
				obj->isFire = true;
				listitems.push_back(DropItem(obj->GetPositionX(), obj->GetPositionY()- monkey_drop_item_y, RandomItems()));
			}
		}

		if (dynamic_cast<Skeleton*>(obj) && obj->GetState() == skeleton_ani_die && !(obj->isDone) && !(obj->isFire))
		{
			if (obj->animation_set->at(skeleton_ani_die)->RenderOver(skeleton_time))
			{
				Skeleton* e = dynamic_cast<Skeleton *>(obj);
				simon->addScore(e->getScore());
				obj->isFire = true;
				listitems.push_back(DropItem(obj->GetPositionX() + skele_drop_item_x, obj->GetPositionY(), RandomItems()));
			}
		}

		if (dynamic_cast<Raven*>(obj) && obj->GetState() == raven_ani_die && !(obj->isDone) && !(obj->isFire))
		{
			if (obj->animation_set->at(raven_ani_die)->RenderOver(raven_time))
			{
				Raven* e = dynamic_cast<Raven*>(obj);
				
				e->isFire = true;
				/*obj->isFire = true;*/
				if (/*!simon->ravendie*/!e->Getcollisimon())
				{
					simon->addScore(e->getScore());
					listitems.push_back(DropItem(obj->GetPositionX(), obj->GetPositionY(), RandomItems()));
				}
				//simon->ravendie = false;
				e->Setcollisimon(false);
			}
		}
		
		if (dynamic_cast<BreakWall*>(obj) && (obj->isDone) && !(obj->isFire))
		{
			obj->isFire = true;

			listpiece.push_back(CreatePiece(obj->x+ piece_0_x, obj->y, piece_type_0));
			listpiece.push_back(CreatePiece(obj->x+ piece_1_x_y, obj->y+ piece_1_x_y, piece_type_1));
			listpiece.push_back(CreatePiece(obj->x + piece_2_x, obj->y - piece_2_y, piece_type_2));
			listpiece.push_back(CreatePiece(obj->x- piece_3_x, obj->y- piece_3_y, piece_type_3));

			if (obj->idItems == items_crown)
			{
				listitems.push_back(DropItem(CGame::GetInstance()->GetCamPosX() + SCREEN_WIDTH / 2, CGame::GetInstance()->GetCamPosY() + SCREEN_HEIGHT - breakwall_drop_item_y_crown, obj->idItems));
			}
			else
				listitems.push_back(DropItem(obj->GetPositionX(), obj->GetPositionY() - breakwall_drop_item_y, obj->idItems));
		}

		if (dynamic_cast<SmallCandle*>(obj) && obj->GetState() == break_candle && !(obj->isDone) && !(obj->isFire))
		{
			if (obj->animation_set->at(break_candle)->RenderOver(smallcandle_time))//để khi render xong lửa thì mới rới đồ
			{
				obj->isFire = true;
				listitems.push_back(DropItem(obj->GetPositionX(), obj->GetPositionY(), obj->idItems));
			}
		}

		if (dynamic_cast<Zombie*>(obj) && obj->GetState() == zombie_ani_die && !(obj->isDone) && !(obj->isFire))
		{
			if (obj->animation_set->at(zombie_ani_die)->RenderOver(zombie_time))
			{
				Zombie* e = dynamic_cast<Zombie *>(obj);
				obj->isFire = true;
				if (e->colliwhip)
				{
					simon->addScore(e->getScore());
					listitems.push_back(DropItem(obj->GetPositionX() + zombie_drop_item_x, obj->GetPositionY(), RandomItems()));
				}
				e->colliwhip = false;
			}
		}

		if (dynamic_cast<Boss*>(obj) && obj->GetState() == boss_ani_die && !(obj->isDone) && !(obj->isFire))
		{
			if (obj->animation_set->at(boss_ani_die)->RenderOver(boss_time))
			{
				Boss* e = dynamic_cast<Boss*>(obj);
				simon->addScore(e->getScore());
				obj->isFire = true;
				listitems.push_back(DropItem(CGame::GetInstance()->GetCamPosX() + (SCREEN_WIDTH / 2), CGame::GetInstance()->GetCamPosY() + ((SCREEN_HEIGHT - boss_drop_item_y) / 2), items_boss));
			}
		}

	}

	

	simon->SimonColliWithItems(&listitems);



	for (int i = 0; i < listitems.size(); i++)
		listitems[i]->Update(dt, &coObjects);


	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects,!timerclk->IsTimeUp());
	}



	simon->Update(dt, &coObjects);
	

	if (simon->GetState() == simon_ani_sit_hit)
		simon->GetWhip()->SetPosWhip(D3DXVECTOR3(simon->GetPositionX(), simon->GetPositionY(), 0), false);//false là ngồi
	else
		simon->GetWhip()->SetPosWhip(D3DXVECTOR3(simon->GetPositionX(), simon->GetPositionY(), 0), true);//true là đứng

	
	
	if (simon->currentWeapon != weapon_watch)
	{
		for (int i = 0; i < max_sub; i++)
		{
			if (simon->currentWeapon != -1 && !simon->GetListSubWeapon()[i]->isDone)
				simon->GetListSubWeapon()[i]->Update(dt, &objects);
		}
	}

		

	float cx, cy;
	simon->GetPosition(cx, cy);


	CGame *game = CGame::GetInstance();

	if (simon->isChangeScene)
	{	
		SwitchScene(simon->nextscene);
		simon->isChangeScene = false;	
	}


	if (boss == nullptr)
	{
		if (simon->GetPositionX() > (SCREEN_WIDTH / 2) && simon->GetPositionX() + (SCREEN_WIDTH / 2) < tilemap->getwidthmap())
		{
			cx = simon->GetPositionX() - (SCREEN_WIDTH / 2);
			CGame::GetInstance()->SetCamPos(cx, 0.0f);
		}
	}
	else
	{
		if (simon->GetPositionX() > (SCREEN_WIDTH / 2) && simon->GetPositionX() + (SCREEN_WIDTH / 2) < tilemap->getwidthmap() && !boss->checkactive)
		{
			cx = simon->GetPositionX() - (SCREEN_WIDTH / 2);
			CGame::GetInstance()->SetCamPos(cx, 0.0f);
		}
		if (boss->checkactive)
			if (simon->x < CGame::GetInstance()->GetCamPosX() - sub_dis_cam_boss)
				simon->x = CGame::GetInstance()->GetCamPosX() - sub_dis_cam_boss;
	}
	
	
	grid->ResetGrid(listpush);

	if (boss == nullptr)
		board->Update(dt, simon->GetHealth(), boss_max_hp);
	else
		board->Update(dt, simon->GetHealth(), boss->hp);

	
	Revival();


	
	
	//DebugOut(L" SO PHAN TU TRONG LISTPIECE %d \n", listpiece.size());

	/*if (simon->bossdie)
	{
		if (!checkreset)
		{
			reset->Start();
			checkreset = true;
		}



		if (simon->GetHealth() < simon_max_health)
		{
			if (delayaddhp->IsTimeUp())
			{
				delayaddhp->Start();
				simon->addHp(1);
			}
		}
		if (simon->getmana() > 0)
		{
			simon->usemana(1);
			simon->addScore(add_score_time_up);
		}

		if (board->gettimemax() > 0)
		{
			board->subtimemax(1);
			simon->addScore(10);
		}

	}*/
	ResetGame();
}

void CPlayScene::Render()
{
	tilemap->Draw();
	board->Render(idstage, CGame::GetInstance()->GetCamPosX(), 0, simon);
	
	
	
	
	/*for (int i = 0; i < liststairleft.size(); i++)
		liststairleft[i]->Render();


	for (int i = 0; i < liststairright.size(); i++)
		liststairright[i]->Render();
*/

	
	for (int i = 0; i < listitems.size(); i++)
		listitems[i]->Render();

	

	for (int i = 0; i < objects.size(); i++)
		if(objects[i]!=dynamic_cast<Ground*>(objects[i]))
			objects[i]->Render();

	for (int i = 0; i < listpiece.size(); i++)
		listpiece[i]->Render();

	simon->Render();

	if (simon->Getnx() > 0)
		simon->GetWhip()->SetNx(1);
	else
		simon->GetWhip()->SetNx(-1);

	if ((simon->GetState() == simon_ani_stand_hit || simon->GetState() == simon_ani_sit_hit || simon->GetState() == simon_ani_stair_down_hit || simon->GetState() == simon_ani_stair_up_hit) && !simon->isHitSubWeapon || (simon->isHitSubWeapon&&simon->currentWeapon == -1))
	{
		simon->GetWhip()->Render(simon->animation_set->at(simon->GetState())->GetcurrentFrame());
	}
	else
		simon->GetWhip()->Render(-1);


	if (simon->currentWeapon != 1)
	{
		for (int i = 0; i < max_sub; i++)
		{
			if (simon->currentWeapon != -1)
			{
				simon->GetListSubWeapon()[i]->Render();
			}

		}
	}
	
	//if(simon->isHitSubWeapon&&simon->currentWeapon!=-1)
		//simon->GetKnife()->Render();
	
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	objects.clear();

	for (int i = 0; i < listitems.size(); i++)
		delete listitems[i];
	listitems.clear();

	for (int i = 0; i < liststairleft.size(); i++)
		delete liststairleft[i];
	liststairleft.clear();

	for (int i = 0; i < liststairright.size(); i++)
		delete liststairright[i];
	liststairright.clear();

	for (int i = 0; i < listpiece.size(); i++)
		delete listpiece[i];
	listpiece.clear();

	listpush.clear();
	listidle.clear();
	
	delete grid;
	delete grididle;
	grid = NULL;
	grididle = NULL;


	boss = nullptr;
}

void CPlayScenceKeyHandler::RunRight()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	simon->SetNx(1);
	simon->SetState(simon_ani_run);
}

void CPlayScenceKeyHandler::RunLeft()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	simon->SetNx(-1);
	simon->SetState(simon_ani_run);
	
}
// ,
void CPlayScenceKeyHandler::Jump()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	if (simon->GetState() == simon_ani_stand_hit || simon->GetState() == simon_ani_sit_hit || simon->GetState() == simon_ani_sit || simon->GetState() == simon_ani_led)
		return;

	if (simon->isGrounded)
		simon->SetState(simon_ani_jump);
}

void CPlayScenceKeyHandler::Idle()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	if (simon->isGrounded)
		simon->SetState(simon_ani_idle);
}

void CPlayScenceKeyHandler::Hit()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	if (simon->isWalkStair)
		return;

	if ((simon->GetState() == simon_ani_idle || simon->GetState() == simon_ani_jump || simon->GetState() == simon_ani_run))
	{
		if (simon->isGrounded)
		{
			simon->SetState(simon_ani_stand_hit);
			simon->SetVx(0);
		}
		else
		{
			simon->SetState(simon_ani_stand_hit);
		}
	}
	else if (simon->GetState() == simon_ani_sit)
		simon->SetState(simon_ani_sit_hit);
	else if (simon->GetState() == simon_ani_stair_up)
		simon->SetState(simon_ani_stair_up_hit);
	else if (simon->GetState() == simon_ani_stair_down)
		simon->SetState(simon_ani_stair_down_hit);
}

void CPlayScenceKeyHandler::Sit()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	simon->SetState(simon_ani_sit);
}

void CPlayScenceKeyHandler::Hit_SubWeapon()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	CPlayScene *playscene = ((CPlayScene*)scence);
	SubWeapon * subweaponlist = NULL;

	if (simon->currentWeapon == weapon_watch)
	{
		subweaponlist = simon->GetListSubWeapon()[first_sub];
		if (simon->getmana() < mana_use)
			return;
		if (!playscene->timerclk->IsTimeUp())
			return;
	}


	if (simon->currentWeapon != -1 && simon->currentWeapon != 1)
	{
		if (!simon->GetListSubWeapon()[first_sub]->isFire)
			subweaponlist = simon->GetListSubWeapon()[first_sub];
		else if (!simon->GetListSubWeapon()[sec_sub]->isFire  && (simon->hitDoubleTriple == 0 || simon->hitDoubleTriple == 1))
			subweaponlist = simon->GetListSubWeapon()[sec_sub];
		else if (!simon->GetListSubWeapon()[last_sub]->isFire && simon->hitDoubleTriple == 1)
			subweaponlist = simon->GetListSubWeapon()[last_sub];
		else 
			return;
	}


	if (simon->currentWeapon == -1||simon->getmana()==0)
	{
		Hit();
		return;  //return để không bị đánh khi không có vũ khí phụ
	}

	if (simon->currentWeapon == weapon_watch)
	{
		simon->usemana(mana_use);
		playscene->timerclk->Start();
	}
	
	if (!subweaponlist->isDone) //để cho vũ khí phụ ko thể đánh quá nhiều
		return;
	simon->isHitSubWeapon = true;

	if (simon->getcurrentweapon() != -1 && simon->currentWeapon != weapon_watch)
	{
		subweaponlist->SetNx(simon->Getnx());
		if (simon->GetState() == simon_ani_sit)       
			subweaponlist->SetPosSubWeapon(D3DXVECTOR3(simon->GetPositionX(), simon->GetPositionY(), 0), false);
		else
			subweaponlist->SetPosSubWeapon(D3DXVECTOR3(simon->GetPositionX(), simon->GetPositionY(), 0), true);
		subweaponlist->SetV();
		subweaponlist->isDone = false;
		subweaponlist->isFire = true;
		simon->usemana(1);
	}
	Hit();
}

void CPlayScenceKeyHandler::Stair_Down()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	int Stairnx = simon->stairNx; //hướng cầu thang


	if (!simon->canmovedownstair)//ra khỏi cầu thang
	{
		if (simon->isStandOnStair)
		{
			float stairx;
			stairx = simon->stairCollided->GetPositionX();
			if (Stairnx == 1)
				stairx -= dis_sub_auto_walk;//31.0f;
			else
				stairx += dis_add_auto_walk;//5;
			simon->nx = simon->stairNx;
			simon->SetState(simon_ani_stair_up);
			simon->AutoWalkStair(stairx, simon_ani_idle, -simon->nx);//tránh trường hợp ra khỏi cầu thang mà ko dụng vào mặt đất
		}
		else { 
			simon->SetState(simon_ani_sit);
			return; 
		}

	}
	


	if (!simon->isStandOnStair)// đi đúng đến vị trí cần đi
	{
		float stairx, simonx;
		stairx =simon->stairCollided->GetPositionX();
		simonx = simon->GetPositionX();
		if (Stairnx == 1)
			stairx += dis_down_st_1;//4.0f;
		else
			stairx -= dis_sub_auto_walk;//31.0f;

		if (stairx < simonx) simon->SetNx(-1);
		else if (stairx > simonx) simon->SetNx(1);
		simon->vy = 0;
		simon->SetState(simon_ani_run);
		simon->AutoWalkStair(stairx, simon_ani_stair_down, -Stairnx);
		simon->isStandOnStair = true;
		return;
	}
	else
	{
		simon->nx = -simon->stairNx;
		simon->SetState(simon_ani_stair_down);

	}
	return;
}

void CPlayScenceKeyHandler::Stair_Up()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	int NxStair = simon->stairNx;

	if (!simon->canmoveupstair) 
	{
		if (simon->isStandOnStair)
		{
			float stairx,sty;
			stairx = simon->stairCollided->GetPositionX();
			if (NxStair == 1)
				stairx += dis_add_auto_walk;//5.0f;
			else
				stairx -= dis_sub_auto_walk_up;//32.0f;
			simon->nx = simon->stairNx;
			simon->SetState(simon_ani_stair_up);
			simon->AutoWalkStair(stairx, simon_ani_idle, simon->nx);//tránh trường hợp ra khỏi cầu thang mà ko dụng vào mặt đất
		}
		return;
	}

	

	if (!simon->isStandOnStair) // đi đúng đến vị trí cần đi
	{
		float stair_x, simon_x;
		stair_x = simon->stairCollided->GetPositionX();
		simon_x = simon->GetPositionX();
		
		
		if (NxStair == 1)
			stair_x -= dis_sub_auto_walk;//31.0f;
		else
			stair_x += dis_up_st;//4.0f;

		if (stair_x < simon_x) simon->SetNx(-1);
		else if (stair_x > simon_x)  simon->SetNx(1);
		simon->SetState(simon_ani_run);
		simon->vy = 0;
		simon->AutoWalkStair(stair_x, simon_ani_stair_up, NxStair);
		simon->isStandOnStair = true;
		return;
	}
	else
	{
		simon->SetNx(NxStair);
		simon->SetState(simon_ani_stair_up);
	}
	return;
}

bool CPlayScenceKeyHandler::Simon_Stair_Stand()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	if (simon->GetState() == simon_ani_stair_up || simon->GetState() == simon_ani_stair_down || simon->GetState() == simon_ani_stair_down_hit || simon->GetState() == simon_ani_stair_up_hit)
	{
		if (simon->GetState() == simon_ani_stair_up_hit)
		{
			simon->SetState(simon_ani_stair_up);
			simon->animation_set->at(simon_ani_stair_up)->startFrameTime = 0;
		}
		else if (simon->GetState() == simon_ani_stair_down_hit)
		{
			simon->SetState(simon_ani_stair_down);
			simon->animation_set->at(simon_ani_stair_down)->startFrameTime = 0;
		}

		simon->StandOnStair();
		simon->animation_set->at(simon_ani_stair_up)->ResetcurrentFrame();
		simon->animation_set->at(simon_ani_stair_down)->ResetcurrentFrame();

		return true;
	}

	return false;
}

bool CPlayScenceKeyHandler::StairCollisionsDetectionLeft()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	CPlayScene* playscene = ((CPlayScene*)scence);
	//simon->StairLeftFirst = true;
	return	simon->SimonColliWithStair(playscene->GetListStairsLeft());
}

bool CPlayScenceKeyHandler::StairCollisionsDetectionRight()
{
	Simon *simon = ((CPlayScene*)scence)->simon;
	CPlayScene* playscene = ((CPlayScene*)scence);
	return	simon->SimonColliWithStair(playscene->GetListStairsRight());
}


void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CGame *game = CGame::GetInstance();
	Simon *simon = ((CPlayScene*)scence)->simon;
	CPlayScene* playscene = ((CPlayScene*)scence);
	switch (KeyCode)
	{
	case DIK_A:
		if (game->IsKeyDown(DIK_UP))
			Hit_SubWeapon();
		else
			Hit();
		break;
	case DIK_S:
		if (simon->isStandOnStair == false && simon->GetState() != simon_ani_hurt)
			Jump();
		break;
	case DIK_Q:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->currentscene = 0;
			simon->nextscene = map1;
			simon->bossdie = false;
			playscene->SwitchScene(map1);
		}
		break;
	case DIK_W:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->currentscene = map1;
			simon->nextscene = map2;
			simon->bossdie = false;
			playscene->SwitchScene(map2);
		}
		break;
	case DIK_E:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->currentscene = map2;
			simon->nextscene = map3;
			simon->bossdie = false;
			playscene->SwitchScene(map3);
		}
		break;
	case DIK_R:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->currentscene = map3;
			simon->nextscene = map4;//4;
			simon->bossdie = false;
			playscene->SwitchScene(map4/*4*/);
		}
		break;
	case DIK_T:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->currentscene = map4;//4;
			simon->nextscene = map5;//5;
			simon->bossdie = false;
			playscene->SwitchScene(5);
		}
		break;
	case DIK_Y:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->currentscene = map5;//5;
			simon->nextscene = map6;//6;
			simon->bossdie = false;
			playscene->SwitchScene(map6);
		}
		break;
	case DIK_0:
		if(simon->GetState()!=simon_ani_dead)
			simon->isCross = true;
		break;
	case DIK_9:
		if (simon->GetState() != simon_ani_dead)
			simon->watertime->Start();
		break;
	case DIK_1:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->InstallKnife();
		}	
		break;
	case DIK_2:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->InstallAxe();
		}
		break;
	case DIK_3:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->InstallBoom();
		}
		break;
	case DIK_4:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->InstallHoly();
		}
		break;
	case DIK_5:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->hitDoubleTriple = 0;
		}
		break;
	case DIK_6:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->hitDoubleTriple = 1;
		}
		break;
	case DIK_7:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->hitDoubleTriple = -1;
		}
		break;
	case DIK_8:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->InstallClk();
		}
		break;
	case DIK_O:
		if (simon->GetState() != simon_ani_dead)
		{
			simon->addHp(simon_max_health);
		}
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	Simon *simon = ((CPlayScene*)scence)->simon;


	if (simon->GetState() == simon_ani_dead||(simon->isWalkStair == true))
		return;


	if (simon->GetState() == simon_ani_stand_hit && simon->animation_set->at(simon_ani_stand_hit)->RenderOver(simon_delay_hit))//để cho ko bị đánh 2 lần
	{
		if (!(simon->isGrounded))
			simon->SetState(simon_ani_jump);
		else
			simon->SetState(simon_ani_idle);
	}

	if (!(simon->isGrounded))
		return;

	if (simon->GetState() == simon_ani_hurt && !(simon->animation_set->at(simon_ani_hurt)->RenderOver(simon_delay_hurt)))
		return;

	if (simon->GetState() == simon_ani_stair_up_hit && !(simon->animation_set->at(simon_ani_stair_up_hit)->RenderOver(simon_delay_hit)))
		return;

	if (simon->GetState() == simon_ani_stair_down_hit && !(simon->animation_set->at(simon_ani_stair_down_hit)->RenderOver(simon_delay_hit)))
		return;

	if (simon->GetState() == simon_ani_stair_up && !(simon->animation_set->at(simon_ani_stair_up)->RenderOver(simon_delay_stair)))
		return;

	if (simon->GetState() == simon_ani_stair_down && !(simon->animation_set->at(simon_ani_stair_down)->RenderOver(simon_delay_stair)))
		return;
	
	if (simon->GetState() == simon_ani_led && !(simon->animation_set->at(simon_ani_led)->RenderOver(simon_delay_led)))
		return;

	if ((simon->GetState() == simon_ani_stand_hit && !(simon->animation_set->at(simon_ani_stand_hit)->RenderOver(simon_delay_hit))) || (simon->GetState() == simon_ani_sit_hit && !simon->animation_set->at(simon_ani_sit_hit)->RenderOver(simon_delay_hit)))
	{	
		return;
	}
	else
	{
		simon->GetWhip()->Setdelaydamage(false);
		simon->isHitSubWeapon = false;
	}

	

	if (game->IsKeyDown(DIK_DOWN))
	{
		if (StairCollisionsDetectionRight() /*&& !simon->StairLeftFirst*/)
		{
			Stair_Down();
			return;
		}

		if (StairCollisionsDetectionLeft())
		{
			Stair_Down();
			return;
		}


		Sit();
		if (game->IsKeyDown(DIK_RIGHT))
			simon->SetNx(1);
		else if (game->IsKeyDown(DIK_LEFT))
			simon->SetNx(-1);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		if (StairCollisionsDetectionLeft())
		{
			//simon->StairLeftFirst = false;
			Stair_Up();
			return;
		}

		if (StairCollisionsDetectionRight())
		{
			//simon->StairLeftFirst = false;
			Stair_Up();
			return;
		}
		Idle();
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (StairCollisionsDetectionRight() || StairCollisionsDetectionLeft())
		{
			if (Simon_Stair_Stand())
				return;
		}
		RunLeft();
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{

		if (StairCollisionsDetectionRight() || StairCollisionsDetectionLeft())
		{
			if (Simon_Stair_Stand())
				return;
		}

		RunRight();
	}
	else
	{
		if (StairCollisionsDetectionRight() || StairCollisionsDetectionLeft())
		{
			if (Simon_Stair_Stand())
			{
				return;
			}
		}
		Idle();
	}
}