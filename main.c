/***************************
 * Name:       main.c      *
 * Programmer: blu.256     *
 * Date:       2021/11/20  *
 ***************************/

#include <termios.h>
#include <unistd.h>
#include <locale.h>
#include <stdio.h>

#include "memory.h"
#include "random.h"

#include "keycodes.h"

#if defined(SAFETY) || defined(EXTENSION_DEBUG)
# include "trace.h"
#endif

#if defined(EXTENSION_DEBUG)
# include "debug.h"
#endif

#if defined(EXTENSION_ANSI)
# include "ansi.h"
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

int is_void(int value)
{
	return !value || value == CR || value == LF;
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

	int success;
	while(! feof(source) )
	{
		buff = getc(source);
		success = 1;

		switch(buff)
		{
			case VAL_INCR:
				++*memptr;
				break;

			case VAL_DECR:
				--*memptr;
				break;

			case PTR_INCR:
				++memptr;
				break;

			case PTR_DECR:
				--memptr;
				break;

			case VAL_RSET:
				*memptr = 0;
				break;

			case PTR_RSET:
				reset_ptr();
				break;

			case VAL_LSFT:
				*memptr = *memptr << 1;
				break;

			case VAL_RSFT:
				*memptr = *memptr >> 1;
				break;

			case VAL_SCAN:
				scanf("%lc", memptr);
				break;

			case VAL_PRIN:
				printf("%lc", *memptr);
				break;

			case SRC_GOTO:
				fseek(source, *memptr, SEEK_SET);
				break;

			case SRC_SEEK:
				fseek(source, *memptr, SEEK_CUR);
				break;

			case JMP_LEFT:
			{
				char tmp = 0;
				int  old = ftell(source);
				while( fseek(source, -2, SEEK_CUR) == 0 )
				{
					tmp = fgetc(source);
					if( tmp == JMP_MARK )
						break;
				}

				if( tmp != JMP_MARK )
					fseek(source, old, SEEK_SET);

				break;
			}

			case JMP_RGHT:
			{
				char tmp = 0;
				int  old = ftell(source);
				while(! feof(source) )
				{
					tmp = getc(source);
					if( tmp == JMP_MARK )
						break;
				}

				if( tmp != JMP_MARK )
					fseek(source, old, SEEK_SET);

				break;
			}

			case JMP_GOTO:
			{
				char tmp       = 0;
				int  occurence = 0;
				int  old       = ftell(source);

				fseek(source, 0, SEEK_SET);
				while(! feof(source) )
				{
					tmp = getc(source);

					if( tmp == JMP_MARK )
					{
						++occurence;
						if( occurence == (int)*memptr )
							break;
					}
				}

				if( occurence == 0 || occurence != (int)*memptr )
					fseek(source, old, SEEK_SET);

				break;
            }

			case CND_SKIP:
				if (is_void(*memptr))
					fseek(source, 1, SEEK_CUR);
				break;

			case CND_TERM:
				if (is_void(*memptr))
				{
					cleanup();
					return 0;
				}
				break;

			case VAL_RAND:
				*memptr = get_rand(*memptr);
				break;

			case VAL_INST:
			{
				int old = ftell(source);
				fseek(source, *memptr, SEEK_SET);
				*memptr = getc(source);
				fseek(source, old, SEEK_SET);
				break;
			}

			case VAL_SWAP:
			{
				wchar_t tmp = *memptr;
				*memptr = reg;
				reg = tmp;
				break;
			}

			case VAL_VTOR:
				reg = *memptr;
				break;

			case VAL_RTOV:
				*memptr = reg;
				break;

			#ifdef EXTENSION_ANSI
			case 88: // X ansi
			{
				char seq[*memptr + 1];
				for (int i = 0; i < *memptr; ++i)
				{
					seq[i] = getc(source);
				}
				seq[*memptr] = '\0';
				ansi(seq);
				break;
			}

			case 34: // " print
			{
				char seq[*memptr + 1];
				for (int i = 0; i < *memptr; ++i)
				{
					seq[i] = getc(source);
				}
				seq[*memptr] = '\0';
				print(seq);
				break;
			}
			#endif

			#ifdef EXTENSION_DEBUG
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

			default:
				success = 0;
				break;
		}

		#if defined(SAFETY) || defined(EXTENSION_DEBUG)
		if( success )
		{
			struct Trace trace = { (int)ftell(source), buff, memptr, *memptr };
			trace_push(trace);
		}
		#endif

		#if defined(SAFETY)
		/* Check position in memory */
		if( memptr >= &memory[ sizeof(memory) / sizeof(memory[0]) ] )
		{
			printf("\nFATAL: tried to access out-of-bounds memory!\n");

			#if defined(EXTENSION_DEBUG)
			debug_print_trace();
			#endif

			cleanup();
			return 2;
		}

		last = buff;
		lptr = memptr;
		#endif
	}

	cleanup();
	return 0;
}
