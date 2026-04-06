#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "includes/grid.h"
#include "includes/error.h"
#include "includes/platform.h"

int main(int argc, char* argv[])
{
	init_terminal();
	atexit(close_terminal);

	clear_screen();

	if (argc < 3) {
		error("Usage: <prog> <height> <width>");
		return EXIT_FAILURE;
	}

	size_t height = (size_t)strtoull(argv[1], NULL, 10);
	size_t width = (size_t)strtoull(argv[2], NULL, 10);

	Grid* grid_current = generate_grid(height, width, 50);
	Grid* grid_next = generate_grid(height, width, 0);
	Cell cursor_position = { 0, 0 };

	char input = 0;

	while (input != 'p') {
		show_grid(grid_current, &cursor_position);

		input = get_key();

		switch (input) {
		case 'w':
			cursor_position.row = (cursor_position.row - 1 + height) % height;
			break;
		case 's':
			cursor_position.row = (cursor_position.row + 1) % height;
			break;
		case 'a':
			cursor_position.column = (cursor_position.column - 1 + width) % width;
			break;
		case 'd':
			cursor_position.column = (cursor_position.column + 1) % width;
			break;
		case 'i':
			grid_current->cells[cursor_position.row][cursor_position.column] = true;
			break;
		case 'o':
			grid_current->cells[cursor_position.row][cursor_position.column] = false;
			break;
		case 'r':
			for (size_t c = 0; c < width; c++)
				grid_current->cells[cursor_position.row][c] = false;
			break;
		case 'R':
			for (size_t c = 0; c < width; c++)
				grid_current->cells[cursor_position.row][c] = true;
			break;
		case 'c':
			for (size_t r = 0; r < height; r++)
				grid_current->cells[r][cursor_position.column] = false;
			break;
		case 'C':
			for (size_t r = 0; r < height; r++)
				grid_current->cells[r][cursor_position.column] = false;
			break;
		case 'q':
			exit(EXIT_SUCCESS);
			break;
		}
	}

	while (true) {
		show_grid(grid_current, NULL);

		update_grid(grid_current, grid_next);

		bool** t = grid_current->cells;
		grid_current->cells = grid_next->cells;
		grid_next->cells = t;

		sleep_for(50);
	}

	destroy_grid(grid_current);
	destroy_grid(grid_next);
	close_terminal();
}