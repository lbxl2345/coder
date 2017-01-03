#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "mpx-out-of-bounds.h"
#include "code.h"
#define noinline __attribute__((noinline))

double pool[2000] = {0xaaaaaaaa};
char dog[] = "dog";
char password[] = "secr3t";
uint64_t temp[2];
unsigned long long GetNtime()
{
	__asm__("RDTSC");
}
noinline
int main(int argc, char **argv){
	
	//printf("%x\n", &temp);
	temp[0] = 0x12345678;
	temp[1] = 0xffffffff;
	clock_t begin, end;
	double loop_t, nop_t, bnd_t, mov_t, ldx_t;
	int i;

	begin = clock();
	__asm__(NOP_CODE);
	end = clock();
	nop_t = (double)(end - begin)/CLOCKS_PER_SEC;
	printf("nop time %f seconds to execute \n", nop_t);

	begin = clock();
	__asm__(BNDCHK_CODE);
	end = clock();
	bnd_t = (double)(end - begin)/CLOCKS_PER_SEC;

	printf("bnd time %f seconds to execute \n", bnd_t);

	begin = clock();
	__asm__(BNDMOV_CODE);
	end = clock();
	mov_t = (double)(end - begin)/CLOCKS_PER_SEC;
	printf("mov time %f seconds to execute \n", mov_t);

	begin = clock();
	__asm__(BNDLDX_CODE);
	end = clock();
	ldx_t = (double)(end - begin)/CLOCKS_PER_SEC;
	printf("ldx time %f seconds to execute \n", ldx_t);
	return 0;
}