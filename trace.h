/***************************
 * Name:       trace.h     *
 * Programmer: blu.256     *
 * Date:       2024/07/05  *
 ***************************/

#ifndef __TRACE__
#define __TRACE__

#include <stddef.h> // wchar_t

struct Trace {
	int       pos;
	char      ins;
	wchar_t*  memptr;
	int       memval;
};

extern struct Trace stack_trace[5];

/* Push a value to the trace stack */
void trace_push(struct Trace trace);

#endif
