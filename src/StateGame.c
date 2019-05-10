#pragma bank 2
#include "main.h"
UINT8 bank_STATE_GAME = 2;

#include "../res/src/tiles.h"
#include "../res/src/map.h"
#include "../res/src/font.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Levels.h"
#include "GameStates.h"
#include "rand.h"
#include "Print.h"

extern UINT8 current_level;
extern const UINT8 num_levels;
extern const struct LevelInfo levels[];

UINT8 collision_tiles[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 253, 0};
UINT8 next_level;

GameState game_state;

void Start_STATE_GAME() {
	UINT8 i;
	const struct LevelInfo* level = &levels[next_level];

	initrand(sys_time);

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, 50, 50);

	InitScrollTiles(0, 80, tiles, 2);
	InitScroll(level->w, level->h, level->map, collision_tiles, 0, level->bank);
	SHOW_BKG;

	game_state.state = PLAYING;
	game_state.door_state = 0;
}

void Update_STATE_GAME() {
	INT8 next;
	UINT8 will_be_next;

	switch (game_state.state)
	{
	case PLAYING:
		break;
	case LEVEL_COMPLETE:
		current_level++;
		
		do
		{
			next = rand();
			if(next < 0) {
				will_be_next = -next % num_levels;
			}
			else {
				will_be_next = next % num_levels;
			}
		} while (will_be_next == next_level);
		
		INIT_CONSOLE(font, 2, 2);
		DPRINT_POS(0, 0);
		DPrintf("rnd: %d, lvl: %d", next, will_be_next);
		
		next_level = will_be_next;
		game_state.door_state = 0;
		SetState(STATE_GAME);
		break;
	default:
		break;
	}
}
