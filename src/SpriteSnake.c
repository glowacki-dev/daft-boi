#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_SNAKE = 2;

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "GameStates.h"

extern GameState game_state;

struct SnakeInfo {
	UINT8 delay;
};

void Start_SPRITE_SNAKE() {
	struct SnakeInfo* data = (struct SnakeInfo*)THIS->custom_data;
	THIS->coll_x = 4;
	THIS->coll_w = 10;
	data->delay = 0;
}

void Update_SPRITE_SNAKE() {
	UINT8 i;
	struct Sprite* spr;
	struct SnakeInfo* data = (struct SnakeInfo*)THIS->custom_data;
	UINT8 move_x = 0, move_y = 0;

	data->delay = (data->delay + 1) % 4;

	if(data->delay == 0) {
		if(THIS->x < game_state.player->x) {
			move_x = 1 << delta_time;
		} else if(THIS->x > game_state.player->x) {
			move_x = -1 << delta_time;
		}

		if(THIS->y < game_state.player->y) {
			move_y = 1 << delta_time;
		} else if(THIS->y > game_state.player->y) {
			move_y = -1 << delta_time;
		}

		TranslateSprite(THIS, move_x, move_y);

		SPRITEMANAGER_ITERATE(i, spr) {
			if(spr != THIS && spr->type == SPRITE_SNAKE) {
				if(CheckCollision(THIS, spr)) {
					TranslateSprite(THIS, -2 * move_x, -2 * move_y);
					return;
				}
			}
		}
	}
}

void Destroy_SPRITE_SNAKE() {
}
