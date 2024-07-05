/***************************
 * Name:       random.h    *
 * Programmer: blu.256     *
 * Date:       2024/07/05  *
 ***************************/

#ifndef __RANDOM__
#define __RANDOM__

#define RAND_SYSTEM  0
#define RAND_OPENSSL 1

/* Initialize random seed */
void rand_init();

/* Get a random value from 0 up to max */
int get_rand(int max);

#endif // __RANDOM__
