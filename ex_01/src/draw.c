#define _POSIX_C_SOURCE 199309L
#include "draw.h"

// If you want you can use the provided struct and static function

typedef struct COLOR_s {
    char r; // red channel
    char g; // green channel
    char b; // blue channel
} COLOR;

static COLOR color_converter(double value) {
    COLOR c;
    c.r = 0;
    c.g = 0;
    c.b = 0;

    // TODO color mapping
    if (value <= 0.5) c.r = 0;
    else if (value >= 0.75) c.r = 255;
    else c.r = ((255-0)/(0.75-0.5))*(value-0.5);

    if (value <= 0.25) c.g = ((255-0)/(0.25-0.0))*(value-0.0);
    else if (value >= 0.75) c.g = ((0-255)/(1.0-0.75))*(value-0.75);
    else c.g = 255;

    if (value <= 0.25) c.b = 255;
    else if (value >= 0.5) c.b = 0;
    else c.b = ((0-255)/(0.5-0.25))*(value-0.25);

    return c;
}



void draw_grid(double* grid, uint32_t x, uint32_t y, const char* filepath) {
    // TODO mandatory
    // Open or create file
    // Write header with meta information
    // Write RGB data
    // Close file
    FILE* file = fopen("result.ppm", "w");
    fprintf(file, "P3\n%d %d\n%d\n", x, y, 255);
    for (int y = 0; y < dy; y++) {
		for (int x = 0; x < dx; x++) {
			fprintf(file, "%d\n", color_converter(grid_source[dx * y + x]));
        }
    }
    fflush(file);
    fclose(file);
}
