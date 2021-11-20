#include <stdint.h>
#include <stdio.h>

#include "memory.c"

void debug_memorymap(uint32_t* memory)
{
	/* X Header */
	printf("  ");
	for( int i = 0; i < MEMX; ++i )
	{
		printf("%i", i % 10);
	}
	printf("\n");

	/* Separator */
	printf(" +");
	for( int i = 0; i < MEMX; ++i )
	{
		printf("-");
	}
	printf("+\n");

	/* Rows */
	for( int y = 0; y < MEMY; ++y )
	{
		/* Y Header */
		printf("%i|", y % 10);
		for( int x = 0; x < MEMX; ++x )
		{
			/* Cell */
			uint32_t m = memory[y * MEMX + x];
			if(!m)
				m = ' ';
			printf("%c", m);
		}
		printf("|\n");
	}

	/* Separator */
	printf(" +");
	for( int i = 0; i < MEMX; ++i )
	{
		printf("-");
	}
	printf("+\n");
}
