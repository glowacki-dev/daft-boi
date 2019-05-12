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

const UINT8 EMPTY_HEART_TILE = 80;
const UINT8 FULL_HEART_TILE = 81;
const UINT8 max_hp = 5;
const UINT8 player_bounce = 16;

const UINT8 sword_frames = 15;
UINT8 cooldown = 0;
UINT8 current_sword_frames = 0;

extern GameState game_state;

void RefreshHp(struct PlayerInfo* player_info)
{
    UINT8 i;

    for(i = 0; i != player_info->hp; i++)
    {
        set_win_tiles(0 + i, 1, 1, 1, &FULL_HEART_TILE);
    }
    for(; i != max_hp; i++)
    {
        set_win_tiles(0 + i, 1, 1, 1, &EMPTY_HEART_TILE);
    }
}

void BouncePlayer(struct Sprite* enemy) {
    // if player is too close to the left wall
    if(THIS->x < 16 + 16 + 1)
    {
        // move player to the right regardless collision coming from right
        TranslateSprite(THIS, (player_bounce + enemy->coll_w), 0);
    }
    // if player is too close to the right wall
    else if(THIS->x > 160 - 16 - 16 - 1)
    {
        // move player to the left regardless collision coming from left
        TranslateSprite(THIS, (-player_bounce - enemy->coll_w), 0);
    }
    else
    {
        // if player is on the left side of enemy
        if(enemy->x >= THIS->x)
        {
            // move player to the left
            TranslateSprite(THIS, -player_bounce, 0);
        }
        //if player is on the right side of enemy
        else
        {
            // move player to the right
            TranslateSprite(THIS, player_bounce, 0);
        }
    }

    // if player is too close to the bottom wall
    if(THIS->y > 144 - 16 - 16 -1)
    {
        // move player to the top regardless collision coming from top
        TranslateSprite(THIS, 0, (-player_bounce - enemy->coll_w));
    }
    // if player is too close to the top wall
    else if(THIS->y < 16 + 16 + 1)
    {
        // move player to the bottom regardless collision coming from bottom
        TranslateSprite(THIS, 0, (player_bounce + enemy->coll_w));
    }
    else
    {
        // if player is on the bottom of enemy
        if(enemy->y >= THIS->y)
        {
            // move player to the bottom
            TranslateSprite(THIS, 0, -player_bounce);
        }
        // if player is on the top of enemy
        else
        {
            // move player to the top
            TranslateSprite(THIS, 0, player_bounce);
        }
    }
}

void Start_SPRITE_PLAYER() {
	struct PlayerInfo* data = (struct PlayerInfo*)THIS->custom_data;
	data->direction_anim = anim_idle;
  if(data->hp == NULL)
  {
      data->hp = max_hp;
  }
	THIS->coll_x = 2;
	THIS->coll_w = 12;
	game_state.player = THIS;
  SpriteManagerAdd(SPRITE_SWORD, THIS->x, THIS->y + 16);
  RefreshHp(data);
}

void Update_SPRITE_PLAYER() {
	UINT8 i;
	struct Sprite* spr;
	struct PlayerInfo* data = (struct PlayerInfo*)THIS->custom_data;
	SPRITE_UNSET_VMIRROR(THIS);

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
  if(KEY_PRESSED(J_B) && data->attack == 0 && cooldown == 0) {
    data->attack = 1;
    current_sword_frames = 10;
    cooldown = 40;
  }

  if(data->attack == 1 && current_sword_frames <= 0)
  {
      data->attack = 0;
      current_sword_frames = 0;
  }
  else if(data->attack == 0 && current_sword_frames == 0 && cooldown > 0)
  {
      cooldown--;
  }
  else
  {
      current_sword_frames--;
  }

	SetSpriteAnim(THIS, data->direction_anim, 10);

	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SPRITE_DOORS) {
			if(CheckCollision(THIS, spr) && game_state.door_state == 1) {
				if(spr->custom_data[0] == 0) { // non-respawn
					game_state.state = LEVEL_COMPLETE;
				} else {
					game_state.state = GOING_TO_RESPAWN;
				}
			}
		} else if(spr->type == SPRITE_SNAKE) {
			if(CheckCollision(THIS, spr)) {
        data->hp--;
        if(data->hp > 0)
        {
            RefreshHp(data);
            BouncePlayer(spr);
        }
        else
        {
            game_state.state = GAME_OVER;
        }
			}
		}
	}
}

void Destroy_SPRITE_PLAYER() {
}
