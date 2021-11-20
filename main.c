#include <stdio.h>
#include <stdint.h>
#include <termios.h>
#include <unistd.h>

#include "memory.c"

#ifdef DEBUG
#include "debug.c"
#endif

static struct termios oldt, newt;

char buff;

void cleanup()
{
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	printf("\n");
}

void term_setup()
{
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;

	/* Do now wait for line breaks */
	newt.c_lflag &= ~ICANON;

	/* No echo */
	newt.c_lflag &= ~ECHO;

	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
}

int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		printf("Usage: duh [source file]\n");
		return 1;
	}

	term_setup();
	reset_ptr();

	FILE *source = fopen(argv[1], "r");

	while( (buff = fgetc(source)) != EOF )
	{
		switch(buff)
		{
			case 43: // + increase value
				++*memptr;
				break;

			case 45: // - decrease value
				--*memptr;
				break;

			case 40: // ( decrease pointer
				--memptr;
				break;

			case 41: // ) increase pointer
				++memptr;
				break;

			case 48: // 0 reset value
				*memptr = 0;
				break;

			case 39: // ' reset pointer
				reset_ptr();
				break;

			case 58: // : get value
				*memptr = getchar();
				break;

			case 59: // ; put value
				putchar(*memptr);
				break;

			#ifdef DEBUG
			case 77: // M memory map
				debug_memorymap(memory);
				break;
			#endif
		}

		#ifdef SAFETY
		if( memptr == &memory[ sizeof(memory) / sizeof(memory[0]) ] )
		{
			printf("\nFATAL: tried to access out-of-bounds memory!\n");
			cleanup();
			return 2;
		}
		#endif
	}

	cleanup();
	return 0;
}
