#pragma bank 2
#include "Levels.h"

#include "../res/src/map.h"
#include "../res/src/map2.h"

#define LEVEL(A, BANK) A##Width, A##Height, A, BANK
const LevelInfo levels[] = {
	{LEVEL(map, 2)},
	{LEVEL(map2, 2)}
};

UINT8 current_level = 0;
const UINT8 num_levels = 2;