#include "grid.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "color.h"
#include "error.h"
#include "platform.h"

void show_grid(const Grid* grid, const Cell* cursor_position)
{
	reset_cursor();

	size_t capacity =
		grid->height * (grid->width + 2) // grid + '\r\n'
		+ 1; // null terminator

	if (cursor_position)
		// ANSI color codes for the cursor
		capacity += strlen(FG_GREEN) + strlen(CLR_RESET);

	char* buffer = malloc(capacity);
	if (!buffer) {
		error("Memory (grid buffer) allocation failed");
		exit(EXIT_FAILURE);
	}

	size_t pos = 0;

	for (size_t r = 0; r < grid->height; r++) {
		for (size_t c = 0; c < grid->width; c++) {
			if (cursor_position && cursor_position->row == r && cursor_position->column == c) {
				strcpy(&buffer[pos], FG_GREEN);
				pos += strlen(FG_GREEN);

				buffer[pos++] = '$';

				strcpy(&buffer[pos], CLR_RESET);
				pos += strlen(CLR_RESET);
			} else if (grid->cells[r][c]) {
				buffer[pos++] = '#';
			} else {
				buffer[pos++] = ' ';
			}
		}

		buffer[pos++] = '\r';
		buffer[pos++] = '\n';
	}

	buffer[pos] = '\0';
	printf(buffer);
	free(buffer);
}

Grid* generate_grid(size_t height, size_t width, uint8_t active_probability)
{
	srand(time(NULL));

	Grid* grid = malloc(sizeof(Grid));

	if (!grid) {
		error("Memory (grid) allocation failed");
		exit(EXIT_FAILURE);
	}

	grid->height = height;
	grid->width = width;

	grid->cells = malloc(height * sizeof(bool*));

	if (!grid->cells) {
		error("Memory (cells) allocation failed");
		exit(EXIT_FAILURE);
	}

	for (size_t r = 0; r < height; r++) {
		grid->cells[r] = malloc(width * sizeof(bool));

		if (!grid->cells[r]) {
			error("Memory (row) allocation failed");
			exit(EXIT_FAILURE);
		}

		for (size_t c = 0; c < width; c++) {
			grid->cells[r][c] = (rand() % 100) < active_probability;
		}
	}

	return grid;
}

void destroy_grid(Grid* grid)
{
	if (!grid)
		return;

	for (size_t r = 0; r < grid->height; r++)
		free(grid->cells[r]);

	free(grid->cells);
	free(grid);
}

uint8_t count_neighbors(const Grid* grid, size_t R, size_t C)
{
	uint8_t neighbor_count = 0;

	size_t r_low = R - 1;
	if (R == 0) r_low = 0;

	size_t r_high = R + 2;
	if (R == grid->height - 1) r_high = grid->height;

	size_t c_low = C - 1;
	if (C == 0) c_low = 0;

	size_t c_high = C + 2;
	if (C == grid->width - 1) c_high = grid->width;

	for (size_t r = r_low; r < r_high; r++) {
		for (size_t c = c_low; c < c_high; c++) {
			if (R == r && C == c)
				continue;
			else if (grid->cells[r][c])
				neighbor_count++;
		}
	}

	return neighbor_count;
}

void update_grid(const Grid* current, Grid* next)
{
	for (int r = 0; r < current->height; r++) {
		for (int c = 0; c < current->width; c++) {
			uint8_t neighbor_count = count_neighbors(current, r, c);

			if (current->cells[r][c])
				next->cells[r][c] = (neighbor_count == 2 || neighbor_count == 3);
			else
				next->cells[r][c] = neighbor_count == 3;
		}
	}
}