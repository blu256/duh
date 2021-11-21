/***************************
 * Name:       memory.c    *
 * Programmer: blu.256     *
 * Date:       2021/11/20  *
 ***************************/

#ifndef __MEMORY__
#define __MEMORY__

#include <stdlib.h>
#include <wchar.h>

#ifndef MEMX
#define MEMX 8
#endif

#ifndef MEMY
#define MEMY 4
#endif

wchar_t  memory[ MEMX * MEMY ];
wchar_t* memptr;
wchar_t  reg;

void reset_ptr()
{
	memptr = &memory[0];
}

#endif // __MEMORY__
