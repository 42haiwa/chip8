#include "chip8.h"

void	cls_memory(Chip8 *chip_8)
{
	for (uint16_t i = 0; i < 0xFFF; i++)
		chip_8->memory[i] = 0;
}

void	cls_screen(Chip8 *chip_8)
{
	for (uint8_t y = 0; y < CHIP8_HEIGHT; y++)
		for (u_int8_t x = 0; x < CHIP8_WIDTH; x++)
			chip_8->screen[x][y] = 0;
}

void	read_opcode(Chip8 *chip_8)
{
	__u_short opcode = (chip_8->memory[chip_8->pc] << 8) |
	 chip_8->memory[chip_8->pc + 1];

	if (chip_8->pc > 0x3FF)
		exit(0);

	f_opcode(opcode, chip_8);

	SDL_Delay(1000 / 10);
}

void	set_pixel(__u_char x, __u_char y, int is_active, Chip8 *chip_8)
{
	chip_8->screen[x][y] ^= is_active;
}

void	draw_screen(SDL_Renderer *renderer, Chip8 *chip_8)
{
	SDL_Rect pixel;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (uint8_t y = 0; y < CHIP8_HEIGHT; y++)
	{
		for (uint8_t x = 0; x < CHIP8_WIDTH; x++)
		{
			if (chip_8->screen[x][y])
			{
				//printf("pixel[%d][%d]\n", x, y);
				pixel.x = x * PIX_SIZE_X;
				pixel.y = y * PIX_SIZE_Y;
				pixel.w = PIX_SIZE_X;
				pixel.h = PIX_SIZE_Y;
				SDL_RenderFillRect(renderer, &pixel);
			}
		}
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

}

void	compute_digits_sprites(Chip8 *chip_8)
{
	(void) chip_8;
// 	fprintf(stdout, "Compute digits sprites in chip8 memory !\n");
// //	0
// 	chip_8->memory[0x600] = 0xF0;
// 	chip_8->memory[0x600 + 1] = 0x90;
// 	chip_8->memory[0x600 + 2] = 0x90;
// 	chip_8->memory[0x600 + 3] = 0x90;
// 	chip_8->memory[0x600 + 4] = 0xF0;

// //	1
// 	chip_8->memory[0x600 + 5] = 0x20;
// 	chip_8->memory[0x600 + 6] = 0x60;
// 	chip_8->memory[0x600 + 7] = 0x20;
// 	chip_8->memory[0x600 + 8] = 0x20;
// 	chip_8->memory[0x600 + 9] = 0x70;
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Unable to init sdl ! %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
	{
		fprintf(stderr, "Error when init window ! %s\n", SDL_GetError());
		return (-1);
	}

	bool running = true;
	SDL_Event event;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// INIT
	
	Chip8 chip_8;
	chip_8.pc = 0x200;
	chip_8.sp = 0;
	chip_8.i = 0;
	memset(chip_8.memory, 0, 4096);
	memset(chip_8.stack, 0, 16 * sizeof(__u_short));
	memset(chip_8.vx, 0, 16);

	cls_memory(&chip_8);

	__u_char *rom_buf = NULL;
	long rom_size;
	read_rom(argv[1], &rom_buf, &rom_size, &chip_8);

	compute_digits_sprites(&chip_8);
	cls_screen(&chip_8);

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
		}
		read_opcode(&chip_8);

		SDL_RenderClear(renderer);
		draw_screen(renderer, &chip_8);
		SDL_RenderPresent(renderer);
	}

	free(rom_buf);	

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}