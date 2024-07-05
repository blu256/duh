/***************************
 * Name:       ansi.h      *
 * Programmer: blu.256     *
 * Date:       2024/07/05  *
 ***************************/

#include <stdio.h>

#include "ansi.h"

void ansi(char* opcode)
{
	printf("%c[%s", 0x1B, opcode);
}

void print(char* string)
{
	printf("%s", string);
}
