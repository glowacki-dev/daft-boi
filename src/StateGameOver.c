#pragma bank 3
#include "main.h"
UINT8 bank_STATE_GAME_OVER = 3;

#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Print.h"

#include "../res/src/end_screen_tile_data.h"
#include "../res/src/end_screen_map_data.h"
#include "../res/src/font.h"

void Start_STATE_GAME_OVER() {
	InitScrollTiles(0, 256, end_screen_tile_data, 3);
	InitScroll(end_screen_map_dataWidth, end_screen_map_dataHeight, end_screen_map_data, 0, 0, 3);
	SHOW_BKG;
	HIDE_WIN;

	INIT_FONT(font, 2, PRINT_BKG);

	PRINT(2, 13, "----------------");
	PRINT(3, 14, "You are ded :(");
	PRINT(2, 15, "Rest in peperoni");
	PRINT(2, 16, "----------------");
}

void Update_STATE_GAME_OVER() {
	if(previous_keys && !keys) {
		SetState(STATE_MENU);
	}
}