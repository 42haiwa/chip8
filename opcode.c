#include "chip8.h"

void	f_opcode(__u_short const opcode, Chip8 *chip_8)
{
	chip_8->pc += 2;
#define DEBUG
#ifdef	DEBUG
	printf("--------------------------\n");
	printf("opcode: 0x%04X\n", opcode);
	printf("pc: 0x%04x\n", chip_8->pc);
	printf("i: 0x%04x\n", chip_8->i);
	printf("--------------------------\n");
#endif
	// for (int i = 0; i <= 0xF; i++)
	// {
	// 	printf("v[%1x] = %d\n", i, chip_8->vx[i]);
	// }
	switch (opcode)
	{
	case 0x00E0:
		cls_screen(chip_8);
		break;
	
	case 0x00EE:
		chip_8->sp--;
		chip_8->pc = chip_8->stack[chip_8->sp];
		break;	

	default:
		switch (opcode & 0xF0FF)
		{
		case 0xE09E:
			__u_short x = (opcode >> 8) & 0x0F;
			printf("\\//\n");
			if (is_pressed(x))
				chip_8->pc += 2;
			break;
		
		case 0xE0A1:
			x = (opcode >> 8) & 0x0F;
			printf("\\//\n");
			if (!is_pressed(x))
				chip_8->pc += 2;
			break;

		case 0xF007:
			x = (opcode >> 8) & 0x0F;
			chip_8->vx[x] = chip_8->dt;
			break;

		case 0xF00A:
			x = (opcode >> 8) & 0x0F;
			exit(0);
			//chip_8->vx[x] = wait_key(); // TODO write wait_key func
			break;

		case 0xF015:
			x = (opcode >> 8) & 0x0F;
			chip_8->dt = chip_8->vx[x];
			break;
		
		case 0xF018:
			x = (opcode >> 8) & 0x0F;
			chip_8->st = chip_8->vx[x];
			break;

		case 0xF01E:
			x = (opcode >> 8) & 0x0F;
			chip_8->i += chip_8->vx[x];
			break;

		case 0xF029:
			x = (opcode >> 8) & 0x0F;
			chip_8->i = chip_8->vx[x] * 5;
			break;

		case 0xF033:
			x = (opcode >> 8) & 0x0F;
			int	_vx = chip_8->vx[x];
			chip_8->memory[chip_8->i] = (_vx - (_vx % 100)) / 100;
			_vx -= chip_8->memory[chip_8->i] * 100;
			chip_8->memory[chip_8->i + 1] = (_vx - (_vx % 10)) / 10;
			_vx -= chip_8->memory[chip_8->i + 1] * 10;
			chip_8->memory[chip_8->i + 2] = _vx;
			break;

		case 0xF055:
			x = (opcode >> 8) & 0x0F;
			for (__u_char i = 0; i <= (__u_char) x; ++i)
				chip_8->memory[chip_8->i + i] = chip_8->vx[i];
			break;

		case 0xF065:
			x = (opcode >> 8) & 0x0F;
			for (__u_char i = 0; i <= (__u_char) x; ++i)
				chip_8->vx[i] = chip_8->memory[chip_8->i + i];
			break;

		default:
			break;
		}
		switch (opcode & 0xF000)
		{
		case 0x1000:
			__u_short jump = opcode & 0x0FFF;
			chip_8->pc = jump;
			break;
		
		case 0x2000:
			__u_short call_addr = opcode & 0x0FFF;
			chip_8->stack[chip_8->sp] = chip_8->pc;
			chip_8->sp++;
			chip_8->pc = call_addr;
			break;
		
		case 0x3000:
			__u_short n_reg = (opcode >> 8) & 0x0F;
			__u_char kk = opcode & 0x00FF;
			if (chip_8->vx[n_reg] == kk)
				chip_8->pc += 2;
			break;

		case 0x4000:
			n_reg = (opcode >> 8) & 0x0F;
			kk = opcode & 0x00FF;
			if (chip_8->vx[n_reg] != kk)
				chip_8->pc += 2;
			break;

		case 0x5000:
			__u_short x = (opcode >> 8) & 0x0F;
			__u_short y = (opcode >> 4) & 0x0F;
			if (chip_8->vx[x] == chip_8->vx[y])
				chip_8->pc += 2;
			break;
		
		case 0x6000:
			x = (opcode >> 8) & 0x0F;
			chip_8->vx[x] = opcode & 0x00FF;
			printf("SET v[%d] = 0x%2X\n", x, opcode & 0x00FF);
			break;
		
		case 0x7000:
			x = (opcode >> 8) & 0x0F;
			chip_8->vx[x] += opcode & 0x00FF;
			break;

		case 0x8000:
			x = (opcode >> 8) & 0x0F;
			y = (opcode >> 4) & 0x0F;
			if ((opcode & 0x000F) == 0)
				chip_8->vx[x] = chip_8->vx[y];

			if ((opcode & 0x000F) == 1)
				chip_8->vx[x] |= chip_8->vx[y];
			
			if ((opcode & 0x000F) == 2)
				chip_8->vx[x] &= chip_8->vx[y];

			if ((opcode & 0x000F) == 3)
				chip_8->vx[x] ^= chip_8->vx[y];

			if ((opcode & 0x000F) == 4)
			{
				int r = chip_8->vx[x] + chip_8->vx[y];
				(r > 255) ? (chip_8->vx[0xF] = 1) : (chip_8->vx[0xF] = 0);
				chip_8->vx[x] = r & 0xFF;
			}

			if ((opcode & 0x000F) == 5)
			{
				(chip_8->vx[x] > chip_8->vx[y]) ? (chip_8->vx[0xF] = 1) : (chip_8->vx[0xF] = 0);
				if (!chip_8->vx[0xF])
					chip_8->vx[x] -= chip_8->vx[y];
			}

			if ((opcode & 0x000F) == 6)
			{
				chip_8->vx[0xF] = chip_8->vx[x] & 1;
				chip_8->vx[x] >>= 1;
			}

			if ((opcode & 0x000F) == 7)
				(chip_8->vx[y] > chip_8->vx[x]) ? (chip_8->vx[0xF] = 1) : (chip_8->vx[x] = chip_8->vx[y] - chip_8->vx[x]);
			
			if ((opcode & 0x000F) == 0xE)
			{
				chip_8->vx[0xF] = chip_8->vx[x] >> 7;
				chip_8->vx[x] <<= 1;
			}

			break;
		
		case 0x9000:
			x = (opcode >> 8) & 0x0F;
			y = (opcode >> 4) & 0x0F;

			if (chip_8->vx[x] != chip_8->vx[y])
				chip_8->pc += 2;
			break;
		
		case 0xA000:
			chip_8->i = opcode & 0x0FFF;
			break;
		
		case 0xB000:
			__u_short addr = opcode & 0x0FFF;
			chip_8->pc = addr + chip_8->vx[0];
			break;
		
		case 0xC000:
			x = (opcode >> 8) & 0x0F;
			__u_char random = rand() % 256;
			kk = opcode & 0x00FF;
			chip_8->vx[x] = random & kk;
			break;

		case 0xD000:
			__u_short n = opcode & 0x000F;
			x = chip_8->vx[(opcode >> 8) & 0x0F]; // Récupérer la valeur de x à partir du registre Vx
			y = chip_8->vx[(opcode >> 4) & 0x0F]; // Récupérer la valeur de y à partir du registre Vx

			uint8_t pixel;

			chip_8->vx[0xF] = 0;

			for (int i = 0; i < n; i++) 
			{
				pixel = chip_8->memory[chip_8->i + i];
				for (int j = 0; j < 8; j++) 
				{
					if ((pixel & (0x80 >> j)) != 0)
					{
						printf("Draw in X: %d, Y: %d\n", x, y);
						if (chip_8->screen[x + j][y + i] == 1) 
						{
							chip_8->vx[0xF] = 1;
						}
						chip_8->screen[x + j][y + i] ^= 1;
					}
				}
			}

			break;

		default:
			break;
		}
		break;
	}
}