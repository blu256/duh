#ifndef __MEMORY__
#define __MEMORY__

#include <stdint.h>
#include <stdlib.h>

#ifndef MEMX
#define MEMX 8
#endif

#ifndef MEMY
#define MEMY 4
#endif

uint32_t  memory[ MEMX * MEMY ];
uint32_t* memptr;


void reset_ptr()
{
	memptr = &memory[0];
}

#endif // __MEMORY__
