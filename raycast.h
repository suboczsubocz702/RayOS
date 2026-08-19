#ifndef RAYCAST_H
#define RAYCAST_H

#include <stdint.h>
#include <stdbool.h>

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define MAP_WIDTH	24
#define MAP_HEIGHT	24

typedef struct {
	double posX, posY;
	double dirX, dirY;
	double planeX, planeY;
	double moveSpeed;
	double rotSpeed;
} player_t;

typedef struct {
	int map[MAP_WIDTH][MAP_HEIGHT];
} world_t;

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} color_rgb_t;

extern player_t player;
extern world_t world;
extern uint32_t framebuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

void raycast_init(void);
void raycast_render(void);
void update_player(bool keys[256], double frameTime);
void put_pixel(int x, int y, uint32_t color);
void clear_screen(uint32_t color);
uint32_t rgb_to_int(color_rgb_t color);
color_rgb_t int_to_rgb(uint32_t color);

#endif
