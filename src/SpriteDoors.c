#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_DOORS = 2;

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "rand.h"
#include "Levels.h"
#include "GameStates.h"

extern UINT8 current_level;
extern const struct LevelInfo levels[];
extern GameState game_state;

struct DoorInfo {
	UINT8 respawn;
    UINT8 sprite_offset;
};

void Start_SPRITE_DOORS() {
    struct DoorInfo* data = (struct DoorInfo*)THIS->custom_data;
	const struct LevelInfo* level = &levels[current_level];

	data->respawn = rand() % 2;

    // Load horizontal and vertical doors + do flipping
    if(THIS->x == 0) {
        SPRITE_SET_VMIRROR(THIS);
        SPRITE_SET_HMIRROR(THIS);
        data->sprite_offset = 3;
    } else if (THIS->x == 8 * level->w - 16) {
        data->sprite_offset = 3;
    } else if (THIS->y == 8 * level->h - 16) {
        SPRITE_SET_HMIRROR(THIS);
        SPRITE_SET_VMIRROR(THIS);
    }
    
    THIS->current_frame = data->sprite_offset;
}

void Update_SPRITE_DOORS() {
    struct DoorInfo* data = (struct DoorInfo*)THIS->custom_data;

    if(KEY_PRESSED(J_A)) {
        game_state.door_state = 1;
	}

    if(game_state.door_state == 1) {
        if(data->respawn == 0) {
            THIS->current_frame = data->sprite_offset + 1;
        } else {
            THIS->current_frame = data->sprite_offset + 2;
        }
    }
}

void Destroy_SPRITE_DOORS() {
}