NAME = so_long
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I RESSOURCES/mlx -I RESSOURCES/libft
SOURCES = $(wildcard SOURCES/*.c)
OBJ = $(SOURCES:.c=.o)
MLXFLAGS = -L RESSOURCES/mlx -lmlx -framework OpenGL -framework AppKit -lz
LIBFTPATH = RESSOURCES/libft/
LIBFT = $(LIBFTPATH)libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFTPATH)

$(NAME): $(SOURCES) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) $(MLXFLAGS) $(LIBFT) -o $(NAME)

obj: $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

debug: $(NAME)
	$(CC) $(CFLAGS) -fsanitize=address -g $(INCLUDES) $(SOURCES) $(MLXFLAGS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(LIBFTPATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTPATH) fclean

re: fclean all

.PHONY: all clean fclean re obj
