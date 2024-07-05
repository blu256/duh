/***************************
 * Name:       memory.h    *
 * Programmer: blu.256     *
 * Date:       2024/07/05  *
 ***************************/

#ifndef __MEMORY__
#define __MEMORY__
#include <stddef.h>

#ifndef MEMX
# define MEMX 8
#endif

#ifndef MEMY
# define MEMY 4
#endif

extern wchar_t  memory[ MEMX * MEMY ];
extern wchar_t* memptr;
extern wchar_t  reg;

/* Reset memory pointer to first memory position */
void reset_ptr();

#endif // __MEMORY__
