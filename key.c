#include "chip8.h"

int		is_pressed(__u_short const key)
{
	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

	switch (key)
	{
	case 0:
		return (keyboard_state[SDL_SCANCODE_0]);
		break;

	case 1:
		return (keyboard_state[SDL_SCANCODE_1]);
		break;

	case 2:
		return (keyboard_state[SDL_SCANCODE_2]);
		break;

	case 3:
		return (keyboard_state[SDL_SCANCODE_3]);
		break;

	case 4:
		return (keyboard_state[SDL_SCANCODE_4]);
		break;

	case 5:
		return (keyboard_state[SDL_SCANCODE_5]);
		break;

	case 6:
		return (keyboard_state[SDL_SCANCODE_6]);
		break;

	case 7:
		return (keyboard_state[SDL_SCANCODE_7]);
		break;

	case 8:
		return (keyboard_state[SDL_SCANCODE_8]);
		break;

	case 9:
		return (keyboard_state[SDL_SCANCODE_9]);
		break;

	case 0xA:
		return (keyboard_state[SDL_SCANCODE_A]);
		break;

	case 0xB:
		return (keyboard_state[SDL_SCANCODE_B]);
		break;

	case 0xC:
		return (keyboard_state[SDL_SCANCODE_C]);
		break;

	case 0xD:
		return (keyboard_state[SDL_SCANCODE_D]);
		break;

	case 0xE:
		return (keyboard_state[SDL_SCANCODE_E]);
		break;

	case 0xF:
		return (keyboard_state[SDL_SCANCODE_F]);
		break;
	
	default:
		break;
	}
	return (0);
}