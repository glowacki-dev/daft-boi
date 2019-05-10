#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_PLAYER = 2;

#include "ZGBMain.h"
#include "Keys.h"
#include "SpriteManager.h"

const UINT8 anim_idle[] = {1, 0};
const UINT8 anim_walk[] = {2, 1, 2};
const UINT8 anim_idle_right[] = {1, 9};
const UINT8 anim_walk_right[] = {2, 4, 5};
const UINT8 anim_idle_up[] = {1, 6};
const UINT8 anim_walk_up[] = {2, 7, 8};

void Start_SPRITE_PLAYER() {
	THIS->coll_x = 2;
	THIS->coll_w = 12;
}

void Update_SPRITE_PLAYER() {
	UINT8 i;
	struct Sprite* spr;

	if(KEY_PRESSED(J_UP)) {
		THIS->custom_data[0] = J_UP;
		TranslateSprite(THIS, 0, -1 << delta_time);
		SetSpriteAnim(THIS, anim_walk_up, 10);
	} 
	if(KEY_PRESSED(J_DOWN)) {
		THIS->custom_data[0] = J_DOWN;
		TranslateSprite(THIS, 0, 1 << delta_time);
		SetSpriteAnim(THIS, anim_walk, 10);
	}
	if(KEY_PRESSED(J_LEFT)) {
		THIS->custom_data[0] = J_LEFT;
		TranslateSprite(THIS, -1 << delta_time, 0);
		SetSpriteAnim(THIS, anim_walk_right, 10);
		SPRITE_SET_VMIRROR(THIS);
	}
	if(KEY_PRESSED(J_RIGHT)) {
		THIS->custom_data[0] = J_RIGHT;
		TranslateSprite(THIS, 1 << delta_time, 0);
		SetSpriteAnim(THIS, anim_walk_right, 10);
		SPRITE_UNSET_VMIRROR(THIS);
	}
	if(keys == 0) {
		switch (THIS->custom_data[0])
		{
		case J_UP:
			SetSpriteAnim(THIS, anim_idle_up, 10);
			break;
		case J_DOWN:
			SetSpriteAnim(THIS, anim_idle, 10);
			break;
		case J_LEFT:
			SetSpriteAnim(THIS, anim_idle_right, 10);
			SPRITE_SET_VMIRROR(THIS);
			break;
		case J_RIGHT:
			SetSpriteAnim(THIS, anim_idle_right, 10);
			SPRITE_UNSET_VMIRROR(THIS);
			break;
		default:
			break;
		}
	}
	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SPRITE_SNAKE) {
			if(CheckCollision(THIS, spr)) {
				SetState(STATE_GAME);
			}
		}
	}
}

void Destroy_SPRITE_PLAYER() {
}