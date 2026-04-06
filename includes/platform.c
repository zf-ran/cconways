#include "platform.h"

#include <stdlib.h>
#include <stdint.h>

#ifdef _WIN32
	#include <windows.h>
	#include <conio.h>
#else
	#include <unistd.h>
	#include <ncurses.h>
#endif

void sleep_for(uint32_t milliseconds)
{
#ifdef _WIN32
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
}

void clear_screen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void reset_cursor()
{
	printf("\033[H");
}

void init_terminal()
{
#ifndef _WIN32
	initscr();
	cbreak();
	noecho();
#endif
}

void close_terminal()
{
#ifndef _WIN32
	endwin();
#endif
}

uint8_t get_key()
{
#ifdef _WIN32
	return _getch();
#else
	return getch();
#endif
}