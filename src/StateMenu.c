#pragma bank 2
#include "main.h"
UINT8 bank_STATE_MENU = 2;

#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/start_screen_tile_data.h"
#include "../res/src/start_screen_map_data.h"

UINT8 collision_tiles[] = {1, 0};

// extern const unsigned char * const polka_start_mod_Data[];
// extern UINT8 current_level;
void Start_STATE_MENU() {
	InitScrollTiles(0, 256, start_screen_tile_data, 3);
	InitScroll(start_screen_map_dataWidth, start_screen_map_dataHeight, start_screen_map_data, 0, 0, 3);
	SHOW_BKG;
	HIDE_WIN;

	// PlayMusic(polka_start_mod_Data, 4, 0);
}

// extern const UINT8 max_energy;
// extern UINT8 current_energy;
void Update_STATE_MENU() {
	if(previous_keys && !keys) {
#ifdef NDEBUG
		// current_level = 0;
#endif 
		// current_energy = max_energy;
		SetState(STATE_GAME);
	}
}