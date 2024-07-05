/***************************
 * Name:       memory.c    *
 * Programmer: blu.256     *
 * Date:       2024/07/05  *
 ***************************/

#include "memory.h"

wchar_t  memory[MEMX * MEMY] = {};
wchar_t *memptr = NULL;
wchar_t  reg;

void reset_ptr()
{
	memptr = &memory[0];
}
