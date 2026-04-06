#ifndef _PLATFORM
#define _PLATFORM

#include <stdint.h>

void sleep_for(uint32_t milliseconds);

void clear_screen();
void reset_cursor();

void init_terminal();
void close_terminal();

uint8_t get_key();

#endif