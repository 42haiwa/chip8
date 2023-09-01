#include "chip8.h"

void	read_rom(char const *path, __u_char **buf, long *rom_size, Chip8 *chip_8)
{
	FILE *file = fopen(path, "rb");

	if (!file)
	{
		fprintf(stderr, "Unable to open rom !\n");
		exit(EXIT_FAILURE);
	}

	fseek(file, 0, SEEK_END);
	*rom_size = ftell(file);
	rewind(file);

	*buf = (__u_char *) malloc(*rom_size);

	if (!(*buf))
	{
		fprintf(stderr, "Unable to allocate memory !\n");
		fclose(file);
		exit(EXIT_FAILURE);
	}

	fread(*buf, 1, *rom_size, file);
	fclose(file);

	for (uint32_t i = 0; i < *rom_size; i += 2)
	{
		__u_short opcode = ((*buf)[i] << 8) | (*buf)[i + 1];
		chip_8->memory[0x200 + i] = (opcode >> 8);
		chip_8->memory[0x200 + i + 1] = (opcode & 0xFF);
		printf("addr 0x%04x => 0x%04X\n", 0x200 + i, opcode);
	}

	printf("%ld bytes readed \n", *rom_size);
}