/***************************
 * Name:       random.c    *
 * Programmer: blu.256     *
 * Date:       2021/11/20  *
 ***************************/

#ifndef __RANDOM__
#define __RANDOM__

#include <time.h>


#if RAND_BACKEND == openssl
#include <openssl/rand.h>
#endif

void rand_init()
{
    srand(time(0));
}

int get_rand(int max) {
    int _num;

    #if RAND_BACKEND == openssl
    unsigned char buffer[1];
    if( RAND_bytes(buffer, 1) == 1 )
        _num = buffer[0] % max;
    else
    #endif

        _num = rand() % max;

    return _num;
}

#endif // __RANDOM__