#pragma bank 2
#include "main.h"
UINT8 bank_STATE_GAME = 2;

#include "../res/src/tiles.h"
#include "../res/src/map.h"
#include "../res/src/hud_window_map.h"
#include "../res/src/font.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Levels.h"
#include "GameStates.h"
#include "rand.h"
#include "Print.h"
#include "Sound.h"

extern UINT8 current_level;
extern const UINT8 num_playable_levels;
extern const struct LevelInfo levels[];
extern UINT8* battle_theme_mod_Data[];

UINT8 collision_tiles[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 253, 0};

GameState game_state;

void Start_STATE_GAME() {
	UINT8 i;
	const struct LevelInfo* level = &levels[current_level];

	initrand(sys_time);

	INIT_CONSOLE(font, 2, 2);

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

  WX_REG = 7;
  WY_REG = 144 - 16;
  SHOW_WIN;
  InitWindow(0, 0, 20, 3, hud_window, 3, 0);

	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, 50, 50);

	InitScrollTiles(0, 84, tiles, 2);
	InitScroll(level->w, level->h, level->map, collision_tiles, 0, level->bank);
	SHOW_BKG;

	game_state.state = PLAYING;
	game_state.door_state = 0;
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
	PlayMusic(battle_theme_mod_Data, 3, 1);

	if(current_level == 0) {
		// Respawn level intro shitty fx 
        PlayFx(CHANNEL_1, 30, 0x7f, 0x58, 0xf7, 0x06, 0x87);
	}
}

void Update_STATE_GAME() {
	INT8 next;
	UINT8 next_level;

	switch (game_state.state)
	{
	case PLAYING:
		DPRINT_POS(0, 1);
		DPrintf("Lvl: %d, w: %d, h: %d     ", current_level, levels[current_level].w, levels[current_level].h);
		break;
	case GOING_TO_RESPAWN:
		current_level = 0;

		game_state.player_hp = MAX_HP;

		DPRINT_POS(0, 0);
		DPrintf("Respawn                  ");

		SetState(STATE_GAME);
		break;
	case LEVEL_COMPLETE:
		// Add points or whatever
		do
		{
			next = rand();
			if(next < 0) {
				next_level = 1 + (-next % num_playable_levels);
			}
			else {
				next_level = 1 + (next % num_playable_levels);
			}
		} while (next_level == current_level);
	
	
		DPRINT_POS(0, 0);
		DPrintf("rnd: %d", next);
		
		current_level = next_level;
		game_state.door_state = 0;
		SetState(STATE_GAME);
		break;
	case GAME_OVER:
		SetState(STATE_GAME_OVER);
		break;
	default:
		break;
	}
}
