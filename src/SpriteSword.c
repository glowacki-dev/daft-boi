#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_SWORD = 2;

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "GameStates.h"

const UINT8 anim_up[] = {1, 1};
const UINT8 anim_down[] = {1, 0};
const UINT8 anim_left[] = {1, 2};
const UINT8 anim_right[] = {1, 3};
const UINT8 anim_hidden[] = {1, 4};

extern GameState game_state;

void Start_SPRITE_SWORD() {
}

void Update_SPRITE_SWORD() {
    UINT8 i;
    struct Sprite* spr;
    struct PlayerInfo* player_info = (struct PlayerInfo*)game_state.player->custom_data;

    if(player_info->attack == 1)
    {
        if(player_info->direction == J_UP)
        {
            TranslateSprite(THIS, 0, -1 << delta_time);
            THIS->x = game_state.player->x;
            THIS->y = game_state.player->y - 16;
            SetSpriteAnim(THIS, anim_up, 10);
        }
        else if(player_info->direction == J_DOWN)
        {
            TranslateSprite(THIS, 0, 1 << delta_time);
            THIS->x = game_state.player->x;
            THIS->y = game_state.player->y + 16;
            SetSpriteAnim(THIS, anim_down, 10);
        }
        else if(player_info->direction == J_LEFT)
        {
            TranslateSprite(THIS, -1 << delta_time, 0);
            THIS->x = game_state.player->x - 12;
            THIS->y = game_state.player->y;
            SetSpriteAnim(THIS, anim_left, 10);
        }
        else if(player_info->direction == J_RIGHT)
        {
            TranslateSprite(THIS, 1 << delta_time, 0);
            THIS->x = game_state.player->x + 12;
            THIS->y = game_state.player->y;
            SetSpriteAnim(THIS, anim_right, 10);
        }
    }
    else
    {
        THIS->x = game_state.player->x;
        THIS->y = game_state.player->y;
        SetSpriteAnim(THIS, anim_hidden, 10);
    }

    SPRITEMANAGER_ITERATE(i, spr) {
        if(spr->type == SPRITE_SNAKE && player_info->attack == 1)
        {
            if(CheckCollision(THIS, spr))
            {
                SpriteManagerRemove(i);
            }
        }
    }
}

void Destroy_SPRITE_SWORD() {
}
