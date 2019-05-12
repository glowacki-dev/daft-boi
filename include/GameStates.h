#ifndef GAME_STATES_H
#define GAME_STATES_H

#include "main.h"
#include "Sprite.h"

typedef enum GameStateEnum {
	PLAYING,
	LEVEL_COMPLETE,
	GOING_TO_RESPAWN,
	GAME_OVER
} GameStateEnum;

struct PlayerInfo {
  UINT8 hp;
  INT8 direction;
  const UINT8 *direction_anim;
  UINT8 attack;
};

typedef struct GameState {
	GameStateEnum state;
	UINT8 door_state;
	struct Sprite* player;
} GameState;

#endif
