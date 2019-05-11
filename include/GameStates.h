#ifndef GAME_STATES_H
#define GAME_STATES_H

#include "main.h"
#include "Sprite.h"

typedef enum GameStateEnum {
	PLAYING,
	LEVEL_COMPLETE,
	GOING_TO_RESPAWN
} GameStateEnum;

typedef struct GameState {
	GameStateEnum state;
	UINT8 door_state;
	struct Sprite* player;
} GameState;

#endif