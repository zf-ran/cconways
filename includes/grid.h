#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Grid of cells for Conway's Game of Life
 *
 * The grid is a 2D array of boolean values where `true` represents a live cell and `false` represents a dead cell.
 */
typedef struct {
	bool** cells; ///< 2D array of the grid
	size_t height;
	size_t width;
} Grid;

/**
 * @brief Position in a grid by row and column
 */
typedef struct {
	size_t row;
	size_t column;
} Cell;

/**
 * @brief Prints the grid to stdout
 *
 * @param grid Pointer to the grid
 * @param cursor_pos Pointer to the current cursor position (can be `NULL`)
 */
void show_grid(const Grid* grid, const Cell* cursor_pos);

/**
 * @brief Creates a new grid with random initial state
 *
 * @param height Number of rows
 * @param width Number of columns
 * @param active_probability Probability percentage (integer from 0 to 100) that a cell starts active
 * @return Pointer to the newly created grid
 */
Grid* generate_grid(size_t height, size_t width, uint8_t active_probability);

/**
 * @brief Frees the memory allocated for the grid
 *
 * @param grid Pointer to the grid to destroy
 */
void destroy_grid(Grid* grid);

/**
 * @brief Counts the number of active neighbors for a cell
 *
 * @param grid Pointer to the grid
 * @param R Row of the cell
 * @param C Column of the cell
 * @return Number of active neighbors (integer from 0 to 8)
 */
uint8_t count_neighbors(const Grid* grid, size_t R, size_t C);

/**
 * @brief Updates the grid to the next generation
 *
 * @param current Pointer to the current grid state
 * @param next Pointer to the grid to store the next state
 */
void update_grid(const Grid* current, Grid* next);