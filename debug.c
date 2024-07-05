/***************************
 * Name:       debug.c     *
 * Programmer: blu.256     *
 * Date:       2024/07/05  *
 ***************************/

#include <stdint.h>
#include <stdio.h>

#include "memory.h"
#include "trace.h"
#include "debug.h"


void debug_print_cell(wchar_t* cell)
{
	printf(
		"&%lx = 0x%x <%lc>\n",
		cell - &memory[0],
		*cell,
		*cell
	);
}

void debug_print_trace()
{
	printf("Stack trace:\n");
	for( int i = 0; i < 5; ++i )
	{
			if(! stack_trace[i].ins )
					continue;

			printf(
					"  %i) Line %i:\t%c\t&%lx = 0x%x <%lc>\n",
					i + 1,
					stack_trace[i].pos,
					stack_trace[i].ins,
					stack_trace[i].memptr - &memory[0],
					stack_trace[i].memval,
					stack_trace[i].memval
			);
	}
}

void debug_memorymap(wchar_t* memory)
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
			wchar_t m = memory[y * MEMX + x];
			if(!m)
				m = ' ';
			printf("%lc", m);
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
