/***************************
 * Name:       random.c    *
 * Programmer: blu.256     *
 * Date:       2024/07/05  *
 ***************************/

#include <time.h>

#if (RAND_BACKEND == RAND_OPENSSL)
# include <openssl/rand.h>
#endif

#include "random.h"

void rand_init()
{
    srand(time(0));
}

int get_rand(int max) {
    int _num;

#if (RAND_BACKEND == RAND_OPENSSL)
    unsigned char buffer[1];
    if( RAND_bytes(buffer, 1) == 1 )
        _num = buffer[0] % max;
    else
#endif

    _num = rand() % max;

    return _num;
}
