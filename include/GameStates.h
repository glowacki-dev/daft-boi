#ifndef GAME_STATES_H
#define GAME_STATES_H

#include "main.h"
#include "Sprite.h"

#define MAX_HP 5

typedef enum GameStateEnum {
	PLAYING,
	LEVEL_COMPLETE,
	GOING_TO_RESPAWN,
	GAME_OVER
} GameStateEnum;

struct PlayerInfo {
  INT8 direction;
  const UINT8 *direction_anim;
  UINT8 attack;
};

typedef struct GameState {
	GameStateEnum state;
	UINT8 door_state;
	struct Sprite* player;
  	UINT8 player_hp;
} GameState;

#endif
