#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_DOORS = 2;

#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "rand.h"
#include "GameStates.h"

extern GameState game_state;

struct DoorInfo {
	UINT8 respawn;
};

void Start_SPRITE_DOORS() {
    struct DoorInfo* data = (struct DoorInfo*)THIS->custom_data;
	data->respawn = rand() % 2;
}

void Update_SPRITE_DOORS() {
    struct DoorInfo* data = (struct DoorInfo*)THIS->custom_data;

    if(KEY_PRESSED(J_A)) {
        game_state.door_state = 1;
	}

    if(game_state.door_state == 1) {
        if(data->respawn == 0) {
            THIS->current_frame = 1;
        } else {
            THIS->current_frame = 2;
        }
    }
}

void Destroy_SPRITE_DOORS() {
}