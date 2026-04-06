#include "error.h"

#include <stdio.h>
#include "color.h"

void error(const char* message)
{
	printf(FG_RED "[ERROR]" CLR_RESET);
	printf(" ");
	printf(message);
}