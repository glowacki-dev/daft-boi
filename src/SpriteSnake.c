#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_SNAKE = 2;

#include "SpriteManager.h"

struct SnakeInfo {
	INT8 vy;
};

void Start_SPRITE_SNAKE() {
	struct SnakeInfo* data = (struct SnakeInfo*)THIS->custom_data;
	data->vy = 1;
}

void Update_SPRITE_SNAKE() {
	struct SnakeInfo* data = (struct SnakeInfo*)THIS->custom_data;
	if(TranslateSprite(THIS, 0, data->vy)) {
		data->vy = -data->vy;
	}
}

void Destroy_SPRITE_SNAKE() {
}