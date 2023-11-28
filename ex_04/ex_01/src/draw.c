#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include "draw.h"

// If you want you can use the provided struct and static function

typedef struct COLOR_s {
    unsigned char r; // red channel
    unsigned char g; // green channel
    unsigned char b; // blue channel
} COLOR;

static COLOR color_converter(double value) {
    COLOR c;
    c.r = 0;
    c.g = 0;
    c.b = 0;

    // TODO color mapping
    if (value <= 0.5) c.r = 0.0;
    else if (value >= 0.75) c.r = 255.0;
    else c.r = ((255.0-0.0)/(0.75-0.5))*(value-0.5);

    if (value <= 0.25) c.g = ((255.0-0.0)/(0.25-0.0))*(value-0.0);
    else if (value >= 0.75) c.g = ((0.0-255.0)/(1.0-0.75))*(value-0.75);
    else c.g = 255.0;

    if (value <= 0.25) c.b = 255.0;
    else if (value >= 0.5) c.b = 0.0;
    else c.b = ((0.0-255.0)/(0.5-0.25))*(value-0.25);

    return c;
}



void draw_grid(double* grid, uint32_t x, uint32_t y, const char* filepath) {
    // TODO mandatory
    // Open or create file
    // Write header with meta information
    // Write RGB data
    // Close file
    FILE* file = fopen(filepath, "w");
    fprintf(file, "P3\n%d %d\n%d\n", x, y, 255);
    for (int dy = 0; dy < y; dy++) {
        for (int dx = 0; dx < x; dx++) {
            COLOR tmp = color_converter(grid[x * dy + dx]);
            fprintf(file, "%u %u %u\n", tmp.r, tmp.g, tmp.b);
        }
    }
    fflush(file);
    fclose(file);
}
