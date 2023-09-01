NAME := chip8
CFLAGS := -Wall -Wextra -Werror
LDFLAGS := -lSDL2

SRC := main.c \
		rom_reader.c \
		opcode.c \
		key.c
OBJ := $(SRC:.c=.o)

%.o:		%.c
				$(CC) $(CFLAGS) $< -c $@

$(NAME):	$(OBJ)
				$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

all:		$(NAME)

clean:
				$(RM) *.o */*.o */*/*.o

fclean:		clean
				$(RM) $(NAME)

re:			fclean	all