/***************************
 * Name:       debug.c     *
 * Programmer: blu.256     *
 * Date:       2024/07/05  *
 ***************************/

#include <stddef.h> // wchar_t

/* Prints the requested value in a verbose manner */
void debug_print_cell(wchar_t* cell);

/* Prints the current call trace */
void debug_print_trace();

/* Prints a representation of the current VM memory */
void debug_memorymap(wchar_t* memory);
