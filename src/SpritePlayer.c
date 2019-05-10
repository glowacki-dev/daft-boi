#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_PLAYER = 2;

#include "ZGBMain.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "GameStates.h"

const UINT8 anim_idle[] = {1, 0};
const UINT8 anim_walk[] = {2, 1, 2};
const UINT8 anim_idle_right[] = {1, 9};
const UINT8 anim_walk_right[] = {2, 4, 5};
const UINT8 anim_idle_up[] = {1, 6};
const UINT8 anim_walk_up[] = {2, 7, 8};

struct PlayerInfo {
	INT8 direction;
	const UINT8 *direction_anim;
};

extern GameState game_state;

void Start_SPRITE_PLAYER() {
	struct PlayerInfo* data = (struct PlayerInfo*)THIS->custom_data;
	data->direction_anim = anim_idle;
	THIS->coll_x = 2;
	THIS->coll_w = 12;
}

void Update_SPRITE_PLAYER() {
	UINT8 i;
	struct Sprite* spr;
	struct PlayerInfo* data = (struct PlayerInfo*)THIS->custom_data;
	SPRITE_UNSET_VMIRROR(THIS);

	if(KEY_PRESSED(J_UP)) {
		data->direction = J_UP;
		data->direction_anim = anim_walk_up;
		TranslateSprite(THIS, 0, -1 << delta_time);
	} 
	if(KEY_PRESSED(J_DOWN)) {
		data->direction = J_DOWN;
		data->direction_anim = anim_walk;
		TranslateSprite(THIS, 0, 1 << delta_time);
	}
	if(KEY_PRESSED(J_LEFT)) {
		data->direction = J_LEFT;
		data->direction_anim = anim_walk_right;
		TranslateSprite(THIS, -1 << delta_time, 0);
		SPRITE_SET_VMIRROR(THIS);
	}
	if(KEY_PRESSED(J_RIGHT)) {
		data->direction = J_RIGHT;
		data->direction_anim = anim_walk_right;
		TranslateSprite(THIS, 1 << delta_time, 0);
	}

	if(keys == 0) {
		switch (data->direction)
		{
		case J_UP:
			data->direction_anim = anim_idle_up;
			break;
		case J_DOWN:
			data->direction_anim = anim_idle;
			break;
		case J_LEFT:
			data->direction_anim = anim_idle_right;
			SPRITE_SET_VMIRROR(THIS);
			break;
		case J_RIGHT:
			data->direction_anim = anim_idle_right;
			break;
		default:
			break;
		}
	}

	SetSpriteAnim(THIS, data->direction_anim, 10);

	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SPRITE_DOORS) {
			if(CheckCollision(THIS, spr) && game_state.door_state == 1) {
				game_state.state = LEVEL_COMPLETE;
			}
		}
	}
}

void Destroy_SPRITE_PLAYER() {
}