/***************************
 * Name:       trace.c     *
 * Programmer: blu.256     *
 * Date:       2021/11/20  *
 ***************************/

#ifndef __TRACE__
#define __TRACE__

struct Trace {
	int       pos;
	char      ins;
	wchar_t*  memptr;
	int       memval;
};

struct Trace stack_trace[5] = {};

void trace_push(struct Trace trace)
{
	for( int i = 4; i > 0; --i )
	{
			stack_trace[i] = stack_trace[i-1];
	}
	stack_trace[0] = trace;
}

#endif