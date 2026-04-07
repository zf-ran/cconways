#pragma once
#include <stdint.h>

/**
 * @brief Sleep for determined time in milliseconds
 *
 * @param milliseconds Sleep time in milliseconds
 */
void sleep_for(uint32_t milliseconds);

/**
 * @brief Clears the screen
 *
 * On Windows calls `cls`, otherwise `clear`.
 */
void clear_screen();

/**
 * @brief Places the cursor in top-left (0, 0) corner
 */
void reset_cursor();

/**
 * @brief Initialize terminal window
 *
 * On Windows do nothing, otherwise initialize `ncurses`.
 */
void init_terminal();

/**
 * @brief Deinitialize terminal window
 *
 * On Windows do nothing, otherwise deinitialize `ncurses`.
 */
void close_terminal();

/**
 * @brief Get user key press.
 *
 * @returns Pressed key (ASCII) code.
 */
uint8_t get_key();