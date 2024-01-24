
#define  _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "string.h"


int main(int argc, char* argv[])
{
	int				 rv = 0;
	unsigned long int rl;

	FILE* in;
	FILE* outL;
	FILE* outH;
	
	int				 idx;
	int				 size;
	int				 misize;

	unsigned char	 rb;
	int				 bc;

	printf("BIN2MIF32 B20230718 qUBECk\n");

	if (argc < 3)
	{
		printf("Bad args\nUSAGE: bin2mif32 input_file.bin output_file.mif\n\n");
		return 1;
	}

	

	in = fopen(argv[1], "rb");
	if (!in)
	{
		printf("ERROR: can't open input file: \"%s\"\n", argv[1]);
		return 1;
	}

	outL = fopen(argv[2], "w");
	if (!outL)
	{
		fclose(in);
		printf("ERROR: can't create output file: \"%s\"\n", argv[2]);
		return 1;
	}


	misize = 32768;

	idx = 0;
	fseek(in, 0L, SEEK_END);
	size = ftell(in);
	fseek(in, 0L, SEEK_SET);

	fprintf(outL, "WIDTH=32;\nDEPTH=%d;\nADDRESS_RADIX=UNS;\nDATA_RADIX=HEX;\nCONTENT BEGIN\n", misize / 4);

	bc = 0;

	for (bc = 0; bc < misize / 4; bc++)
	{

		if (!feof(in))
		{
			rb = fgetc(in);
		}
		else
		{
			rb = 0;
		}
		
		rl = rb;

		if (!feof(in))
		{
			rb = fgetc(in);
		}
		else
		{
			rb = 0;
		}

		rl |= rb << 8;

		if (!feof(in))
		{
			rb = fgetc(in);
		}
		else
		{
			rb = 0;
		}

		rl |= rb << 16;

		if (!feof(in))
		{
			rb = fgetc(in);
		}
		else
		{
			rb = 0;
		}

		rl |= rb << 24;

		fprintf(outL, "\t%d : %08x;\n", bc, rl);

	}

	fprintf(outL, "END;\n");

	fclose(in);
	fclose(outL);


	printf("Conversion done. Saved %d bytes\n\n", size);


	return rv;
}

