#pragma bank 2
#include "Levels.h"

#include "../res/src/map.h"
#include "../res/src/map2.h"

#define LEVEL(A, BANK) A##Width, A##Height, A, BANK
const struct LevelInfo levels[] = {
	{LEVEL(map, 3)},
	{LEVEL(map2, 3)}
};

UINT8 current_level = 0;
const UINT8 num_levels = 2;