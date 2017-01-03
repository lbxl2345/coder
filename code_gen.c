#include <stdio.h>
#include <stdint.h>
int gen_mov(uint32_t addr, int size);
int gen_chk(uint32_t addr, int size);
int gen_ldx(uint32_t addr, int size);
int gen_nop(int size);
int main()
{
	uint32_t addr;
	int size;
	scanf("0x%x,%d", &addr, &size);
	gen_mov(addr, size);
	printf("\n");
	gen_chk(addr, size);
	printf("\n");
	gen_ldx(addr, size);
	printf("\n");
	gen_nop(size);
}
int gen_nop(int size)
{
	int i;
	printf("#define NOP_CODE ");
	printf("\".byte");
	for(i = 0; i < size; i++)
	{
		if(i<size-1)
			printf(" 0x90,");
		else
			printf(" 0x90");
	}
	printf("\"");
}
int gen_mov(uint32_t addr, int size)
{
	uint32_t p = addr;
	int i;
	printf("#define BNDMOV_CODE ");
	printf("\".byte");
	for(i = 0; i < size; i++)
	{
		unsigned char byte[4];
		byte[0] = p &  0x000000ff;
		byte[1] = p >> 8 & 0x000000ff;
		byte[2] = p >> 16 & 0x000000ff;
		byte[3] = p >> 24 & 0x000000ff;
		if(i<size-1)
			printf(" 0x66, 0x0f, 0x1b, 0x14, 0x25, 0x%02x, 0x%02x, 0x%02x, 0x%02x,", byte[0], byte[1], byte[2], byte[3]);
		else
			printf(" 0x66, 0x0f, 0x1b, 0x14, 0x25, 0x%02x, 0x%02x, 0x%02x, 0x%02x", byte[0], byte[1], byte[2], byte[3]);
		p = p + 16;
	}
	printf("\"");
}
int gen_chk(uint32_t addr, int size)
{
	uint32_t p = addr;
	int i;
	printf("#define BNDCHK_CODE ");
	printf("\".byte");
	for(i = 0; i < size; i++)
	{
		unsigned char byte[4];
		byte[0] = p &  0x000000ff;
		byte[1] = p >> 8 & 0x000000ff;
		byte[2] = p >> 16 & 0x000000ff;
		byte[3] = p >> 24 & 0x000000ff;
		if(i<size-1)
			printf(" 0xf3, 0x0f, 0x1a, 0x1c, 0x25, 0x%02x, 0x%02x, 0x%02x, 0x%02x,", byte[0], byte[1], byte[2], byte[3]);
		else
			printf(" 0xf3, 0x0f, 0x1a, 0x1c, 0x25, 0x%02x, 0x%02x, 0x%02x, 0x%02x", byte[0], byte[1], byte[2], byte[3]);
		p = p + 16;
	}
	printf("\"");
}
int gen_ldx(uint32_t addr, int size)
{
	uint32_t p = addr;
	int i;
	printf("#define BNDLDX_CODE ");
	printf("\".byte");
	for(i = 0; i < size/2; i++)
	{
		unsigned char byte[4];
		byte[0] = p &  0x000000ff;
		byte[1] = p >> 8 & 0x000000ff;
		byte[2] = p >> 16 & 0x000000ff;
		byte[3] = p >> 24 & 0x000000ff;
		printf(" 0x0f, 0x1b, 0x1c, 0x25, 0x%02x, 0x%02x, 0x%02x, 0x%02x,", byte[0], byte[1], byte[2], byte[3]);
	}
	for(i = 0; i < size/2; i++)
	{
		unsigned char byte[4];
		byte[0] = p &  0x000000ff;
		byte[1] = p >> 8 & 0x000000ff;
		byte[2] = p >> 16 & 0x000000ff;
		byte[3] = p >> 24 & 0x000000ff;
		if(i<size/2-1)
			printf(" 0x0f, 0x1a, 0x1c, 0x25, 0x%02x, 0x%02x, 0x%02x, 0x%02x,", byte[0], byte[1], byte[2], byte[3]);
		else
			printf(" 0x0f, 0x1a, 0x1c, 0x25, 0x%02x, 0x%02x, 0x%02x, 0x%02x", byte[0], byte[1], byte[2], byte[3]);
	}
	printf("\"");
}