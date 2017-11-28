#include "stdlib.h"

static unsigned int seed = 1;

extern C void srandom(unsigned int new_seed){
	seed = new_seed;
}

extern C long int random(void){
	//Linear congruential generator.
	const unsigned int m = 1 << 31;
	const unsigned int a = 1103515245;
	const unsigned int c = 12345;

	seed = (a * seed + c) % m;
	return seed;
}