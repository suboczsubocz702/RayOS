#include <stdint.h>
#include <stdbool.h>

#define VGA_WIDTH  320
#define VGA_HEIGHT 200
#define VGA_MEMORY 0xA0000

static uint8_t* vga_buffer = (uint8_t*)VGA_MEMORY;
static bool graphics_initialized = false;

void set_vga_mode_13h(void) {
	__asm__ volatile (
			"mov $0x13, %%ax\n"
			"int $0x10\n"
			: : : "eax"
			);
	graphics_initialized = true;
}

void set_text_mode(void) {
	__asm__ volatile (
			"mov $0x03, %%ax\n"
			"int $0x10\n"
			: : : "eax"
			);
	graphics_initialized = false;
}

void put_pixel(int x, int y, uint32_t color) {
	if (graphics_initialized && x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT) {
		vga_buffer[y * VGA_WIDTH + x] = (uint8_t)(color & 0xFF);
	}
}

void clear_screen(uint32_t color) {
	if (!graphics_initialized) return;
	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		vga_buffer[i] = (uint8_t)(color & 0xFF);
	}
}

void draw_vline(int x, int y1, int y2, uint32_t color) {
	if (!graphics_initialized || x < 0 || x >= VGA_WIDTH) return;
	if (y1 > y2) { int temp = y1; y1 = y2; y2 = temp; }
	if (y1 < 0) y1 = 0;
	if (y2 >= VGA_HEIGHT) y2 = VGA_HEIGHT - 1;

	uint8_t col = (uint8_t)(color & 0xFF);
	for (int y = y1; y <= y2; y++) {
		vga_buffer[y * VGA_WIDTH + x] = col;
	}
}
