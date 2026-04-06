#ifndef _GRID
#define _GRID

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	bool** cells;
	size_t height;
	size_t width;
} Grid;

typedef struct {
	size_t row;
	size_t column;
} Cell;

void show_grid(const Grid* grid, const Cell* cursor_pos);
Grid* generate_grid(size_t height, size_t width, uint8_t active_probability);
void destroy_grid(Grid* grid);
uint8_t count_neighbors(const Grid* grid, size_t R, size_t C);
void update_grid(const Grid* current, Grid* next);

#endif