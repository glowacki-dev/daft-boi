#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_DOORS = 2;

#include "SpriteManager.h"
#include "Keys.h"
#include "GameStates.h"

extern GameState game_state;

void Start_SPRITE_DOORS() {
}

void Update_SPRITE_DOORS() {
    if(KEY_PRESSED(J_A)) {
        game_state.door_state = 1;
	}

    THIS->current_frame = game_state.door_state;
}

void Destroy_SPRITE_DOORS() {
}