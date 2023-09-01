#ifndef CHIP8_H
# define CHIP8_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include <SDL2/SDL.h>

#define WIDTH 1280
#define HEIGHT 640

#define CHIP8_WIDTH 64
#define CHIP8_HEIGHT 32

#define PIX_SIZE_X (WIDTH / CHIP8_WIDTH)
#define PIX_SIZE_Y (HEIGHT / CHIP8_HEIGHT)

typedef struct chip8
{
	__u_char	memory[4096];
	__u_char	screen[CHIP8_WIDTH][CHIP8_HEIGHT];
	__u_short	stack[16];
	
	__u_char	vx[16];
	__u_short	i;
	__u_short	pc;
	__u_short	sp;
	__u_char	dt;
	__u_char	st;
} Chip8;

// rom_reader.c
void	read_rom(char const *path, __u_char **buf, long *rom_size, Chip8 *chip_8);

// opcode.c
void	f_opcode(__u_short const opcode, Chip8 *chip_8);

// key.c
int		is_pressed(__u_short const key);

// main.c
void	cls_memory(Chip8 *chip_8);
void	cls_screen(Chip8 *chip_8);
void	read_opcode(Chip8 *chip_8);
void	set_pixel(__u_char x, __u_char y, int is_active, Chip8 *chip_8);
void	draw_screen(SDL_Renderer *renderer, Chip8 *chip_8);
void	compute_digits_sprites(Chip8 *chip_8);
#endif