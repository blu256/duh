/***************************
* Name:       main.c      *
* Programmer: blu.256     *
* Date:       2021/11/20  *
***************************/

#include <termios.h>
#include <unistd.h>
#include <locale.h>
#include <stdio.h>

#include "memory.c"
#include "random.c"

#if defined(SAFETY) || defined(DEBUG)
#include "trace.c"
#endif

#ifdef DEBUG
#include "debug.c"
#endif

static struct termios oldt, newt;

char buff;

#ifdef SAFETY
wchar_t* lptr;
char     last;
#endif


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
	rand_init();
	setlocale(LC_CTYPE, "");

	FILE *source = fopen(argv[1], "r");

	while(! feof(source) )
	{
		buff = getc(source);
		
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
				scanf("%lc", memptr);
				break;

			case 59: // ; put value
				printf("%lc", *memptr);
				break;

			case 64: // @ goto
				fseek(source, *memptr, SEEK_SET);
				break;

			case 95: // _ jump to first | to the left
			{
				char tmp = 0;
				int  old = ftell(source);
				while( fseek(source, -2, SEEK_CUR) == 0 )
				{
					tmp = fgetc(source);
					if( tmp == 124 )
						break;
				}

				if( tmp != 124 )
					fseek(source, old, SEEK_SET);

				break;
			}

			case 61: // = jump to first | to the right
			{
				char tmp = 0;
				int  old = ftell(source);
				while(! feof(source) )
				{
					tmp = getc(source);
			
					if( tmp == 124 )
						break;
				}

				if( tmp != 124 )
					fseek(source, old, SEEK_SET);

				break;
			}

			case 35: // # jump to | by value
			{
				char tmp       = 0;
				int  occurence = 0;
				int  old       = ftell(source);

				fseek(source, 0, SEEK_SET);
				while(! feof(source) )
				{
					tmp = getc(source);

					if( tmp == 124 )
					{
						++occurence;
						if( occurence == *memptr )
							break;
					}
				}

				if( occurence == 0 || occurence != *memptr )
					fseek(source, old, SEEK_SET);

				break;
            }

			case 94: // ^ seek
				fseek(source, *memptr, SEEK_CUR);
				break;

			case 38: // & if zero, skip next instruction
				if(!*memptr)
					fseek(source, 1, SEEK_CUR);
				break;

			case 96: // ` if zero, exit
				if(!*memptr)
				{
					cleanup();
					return 0;
				}
				break;

			case 42: // * rand() < current value
				*memptr = get_rand(*memptr);
				break;

			case 126: // ~ swap cell with register
				wchar_t tmp = *memptr;
				*memptr = reg;
				reg = tmp;
				break;

			#ifdef DEBUG
			case 84: // T stack trace
				debug_print_trace();
				break;

			case 77: // M memory map
				debug_memorymap(memory);
				break;

			case 80: // P print cell
				debug_print_cell(memptr);
				break;

			case 82: // R print register
				debug_print_cell(&reg);
				break;
			#endif
		}

		#ifdef DEBUG
		struct Trace trace = { (int)ftell(source), buff, memptr, *memptr };
		trace_push(trace);
		#endif

		#ifdef SAFETY
		/* Check position in memory */
		if( memptr == &memory[ sizeof(memory) / sizeof(memory[0]) ] )
		{
			printf("\nFATAL: tried to access out-of-bounds memory!\n");

			#ifdef DEBUG
			debug_print_trace();
			#endif

			cleanup();
			return 2;
		}

		/* Check for infinite loops (simple) */
		if( buff == last && buff == 64 && lptr == memptr )
		{
			printf("\nFATAL: infinite loop!\n");

			#ifdef DEBUG
			debug_print_trace();
			#endif

			cleanup();
			return 3;
		}

		/* Check for infinite loops (stack trace) */
		if( buff == 64 )
		{
			for( int i = 0; i < 10; i += 2 )
			{
				if( stack_trace[i].pos == ftell(source) )
				{
					printf("\nFATAL: infinite loop!\n");

					#ifdef DEBUG
					debug_print_trace();
					#endif

					cleanup();
					return 3;
				}
			}
		}

		last = buff;
		lptr = memptr;
		#endif
	}

	cleanup();
	return 0;
}
