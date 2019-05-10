#pragma bank 2
#include "main.h"
UINT8 bank_STATE_GAME = 2;

#include "../res/src/tiles.h"
#include "../res/src/map.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Levels.h"
#include "GameStates.h"

extern UINT8 current_level;
extern const UINT8 num_levels;
extern const struct LevelInfo levels[];

UINT8 collision_tiles[] = {1, 2, 253, 0};

GameState game_state;

void Start_STATE_GAME() {
	UINT8 i;
	const struct LevelInfo* level = &levels[current_level];

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, 50, 50);

	InitScrollTiles(0, 3, tiles, 2);
	InitScroll(level->w, level->h, level->map, collision_tiles, 0, level->bank);
	SHOW_BKG;

	game_state.state = PLAYING;
	game_state.door_state = 0;
}

void Update_STATE_GAME() {
	UINT8 i;
	struct Sprite* spr;

	switch (game_state.state)
	{
	case PLAYING:
		break;
	case LEVEL_COMPLETE:
		current_level++;
		game_state.door_state = 0;
		SetState(current_level == num_levels ? STATE_MENU : STATE_GAME);
		break;
	default:
		break;
	}
}
