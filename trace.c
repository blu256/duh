/***************************
 * Name:       trace.c     *
 * Programmer: blu.256     *
 * Date:       2024/07/05  *
 ***************************/

#include "trace.h"

struct Trace stack_trace[5] = {};

void trace_push(struct Trace trace)
{
	for( int i = 4; i > 0; --i )
	{
			stack_trace[i] = stack_trace[i-1];
	}
	stack_trace[0] = trace;
}
