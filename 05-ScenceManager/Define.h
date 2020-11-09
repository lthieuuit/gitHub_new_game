///
/// SIMON
/// 
#define SIMON_WALKING_SPEED											0.1f
#define SIMON_JUMP_SPEED_Y									0.5f
#define SIMON_JUMP_DEFLECT_SPEED									0.2f
#define SIMON_GRAVITY										0.002f
#define SIMON_DIE_DEFLECT_SPEED										0.002f

#define SIMON_ATTACK_TIME									400
#define SIMON_UNTOUCHABLE_TIME										5000
#define SIMON_RESET_JUMP_TIME								500

#define SIMON_STATE_IDLE											0
#define SIMON_STATE_WALKING									1001
#define SIMON_STATE_JUMP											1002
#define SIMON_STATE_SIT_DOWN								1003
#define SIMON_STATE_HIT												1004
#define SIMON_STATE_SIT_HIT									1005
#define SIMON_STATE_STAIR_UP										1006
#define SIMON_STATE_STAIR_DOWN								1007
#define SIMON_STATE_STAIR_UP_HIT									1008
#define SIMON_STATE_STAIR_DOWN_HIT							1009
#define SIMON_STATE_STAIR_HURT										1010
#define SIMON_STATE_DIE										1011

#define SIMON_ANI_IDLE												0
#define SIMON_ANI_WALKING									1
#define SIMON_ANI_JUMP												2
#define SIMON_ANI_SIT_DOWN									3
#define SIMON_ANI_STAND_HIT											4
#define SIMON_ANI_SIT_HIT									5
#define SIMON_ANI_LED												6
#define SIMON_ANI_STAIR_UP									7
#define SIMON_ANI_STAIR_DOWN										8
#define SIMON_ANI_STAIR_UP_HIT								9
#define SIMON_ANI_STAIR_DOWN_HIT									10
#define SIMON_ANI_STAIR_HURT								11
#define SIMON_ANI_DIE												12
#define SIMON_ANI_WHIP_LV1									13
#define SIMON_ANI_WHIP_LV2											14
#define SIMON_ANI_WHIP_LV4									15

#define SIMON_HEGHT													61
#define SIMON_WIDTH											33
#define SIMON_HEGHT_RESET_SIT										4
#define SIMON_WIDTH_RESET_ATTACK							7

///
/// WEAPON
/// 

#define WEAPON_STATE_HIDDEN											0
#define WEAPON_STATE_ATTACK									1

#define WEAPON_ATTACK_TIME											500

#define WEAPON_ANI_1										0
#define WEAPON_ANI_2												1
#define WEAPON_ANI_3										2

#define WEAPON_X													10
#define WEAPON_Y											15
#define WEAPON_WIDHT_ANI_1											44;
#define WEAPON_HEGTH_ANI_1									23;

///
/// PLAY SENCE
/// 

#define SCREEN_WIDTH												512
#define SCREEN_HEIGHT										448

#define SCENE_SECTION_UNKNOWN										-1
#define SCENE_SECTION_TEXTURES								2
#define SCENE_SECTION_SPRITES										3
#define SCENE_SECTION_ANIMATIONS							4
#define SCENE_SECTION_ANIMATION_SETS								5
#define SCENE_SECTION_OBJECTS								6
#define SCENE_SECTION_LOADMAP										7

#define OBJECT_TYPE_SIMON									0
#define OBJECT_TYPE_BRICK											1
#define OBJECT_TYPE_GOOMBA									2
#define OBJECT_TYPE_KOOPAS											3
#define OBJECT_TYPE_MAP										4
#define OBJECT_TYPE_WEAPON											5
#define OBJECT_TYPE_BOARD									8
#define OBJECT_TYPE_AXE												9
#define OBJECT_TYPE_ZOMBIE									10
#define OBJECT_TYPE_BLACK_LEOPARD									11
#define OBJECT_TYPE_ITEM									12
#define OBJECT_TYPE_PORTAL											50

#define ID_ITEM_TYPE_GOODS									0
#define ID_ITEM_TYPE_TORCH											1
#define ID_ITEM_TYPE_CANDLE									2

#define MAX_SCENE_LINE												1024


///
/// ZOMBIE
/// 

#define ZOMBIE_WALKING_SPEED_X								0.13f
#define ZOMBIE_WALKING_SPEED_Y										0.2f
#define ZOMBIE_GRAVITY										0.001f

#define ZOMBIE_BBOX_WIDTH											32
#define ZOMBIE_BBOX_HEIGHT									64
#define BLACK_LEOPARD_ACTIVE_BBOX_WIDTH								100
#define BLACK_LEOPARD_ACTIVE_BBOX_HEIGHT					200

#define BLACK_LEOPARD_ACTIVE										0    
#define BLACK_LEOPARD_DESTROYED								1
#define ZOMBIE_WALKING												2

#define ZOMBIE_ANI_WALKING									0
#define BLACK_LEOPARD_ANI_IDLE										1
#define BLACK_LEOPARD_ANI_RUN_RIGHT							2
#define BLACK_LEOPARD_ANI_JUMP										3

///
/// ITEM
/// 

#define ITEM_GRAVITY										0.00005f
#define ITEM_TIME_FIRE												500

#define ITEM_DISAPPEAR_TIME									5000
#define ITEM_ANI_ROI												0
#define ITEM_ANI_TIM										1
#define ITEM_ANI_MONEY_BAG											2
#define ITEM_ANI_HOLY_WATER									3
#define ITEM_ANI_MEAT												4
// item phu
#define ITEM_ANI_TORCH										18
#define ITEM_ANI_CANDLE												19
#define ITEM_ANI_FIRE										20


#define ITEM_HEIGHT_ID_ANI_TORCH									64
#define ITEM_WIDTH_ID_ANI_TORCH								32
#define ITEM_HEIGHT_ID_ANI_CANDLE									15
#define ITEM_WIDTH_ID_ANI_CANDLE							15

#define ITEM_HEIGHT_ID_ANI_0										32
#define ITEM_WIDTH_ID_ANI_0									32
#define ITEM_HEIGHT_ID_ANI_1										20
#define ITEM_WIDTH_ID_ANI_1									24
#define ITEM_HEIGHT_ID_ANI_2										30
#define ITEM_WIDTH_ID_ANI_2									30
#define ITEM_HEIGHT_ID_ANI_3										28
#define ITEM_WIDTH_ID_ANI_3									32
#define ITEM_HEIGHT_ID_ANI_4										26
#define ITEM_WIDTH_ID_ANI_4									32