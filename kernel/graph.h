#ifndef GRAPH_H
#define GRAPH_H
#include <stdint.h>

typedef struct {
    uint32_t framebuffer;
    uint32_t width;
    uint32_t height;
    uint32_t bpp;
    uint32_t pitch;
} vesa_mode_info_t;

extern vesa_mode_info_t vesa_info;

void vesa_init(uint32_t fb, uint32_t w, uint32_t h, uint32_t bpp, uint32_t pitch);
void vesa_clear(uint32_t color);
void vesa_put_pixel(int x, int y, uint32_t color);
void vesa_draw_rect(int x, int y, int w, int h, uint32_t color);

void vesa_draw_char(int x, int y, char c, uint32_t color);
void vesa_draw_string(int x, int y, const char* str, uint32_t color);

#endif
