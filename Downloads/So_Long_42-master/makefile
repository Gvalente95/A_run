NAME = so_long
EDITOR_NAME = editor
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I RESSOURCES/mlx -I RESSOURCES/libft
SOURCES = $(wildcard C_FILES/*.c)
COMMON_SOURCES = $(filter-out C_FILES/map_gen.c C_FILES/0_main.c C_FILES/11_map_editor.c, $(wildcard C_FILES/*.c))
VALID_SOURCE = $(wildcard C_FILES/valid_project/*.c)

OBJ = $(SOURCES:.c=.o)
MLXFLAGS = -L RESSOURCES/mlx -lmlx -framework OpenGL -framework AppKit -lz
LIBFTPATH = RESSOURCES/libft/
LIBFT = $(LIBFTPATH)libft.a

GENMAP = rmap

all: $(LIBFT) $(NAME)

gen:
	CC C_FILES/map_gen.c $(INCLUDES) $(LIBFT) -o $(GENMAP)

$(LIBFT):
	make -C $(LIBFTPATH)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(COMMON_SOURCES) $(VALID_SOURCE) $(MLXFLAGS) $(LIBFT) -o $(NAME)

map: $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(COMMON_SOURCES) C_FILES/11_map_editor.c $(MLXFLAGS) $(LIBFT) -o $(EDITOR_NAME)

obj: $(OBJ)

valid: $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(COMMON_SOURCES) C_FILES/0_main.c $(MLXFLAGS) $(LIBFT) -o $(NAME)

valid_debug: $(NAME)
	$(CC) $(CFLAGS) -fsanitize=address -g $(INCLUDES) $(COMMON_SOURCES) $(VALID_SOURCE) $(MLXFLAGS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

debug: $(NAME)
	$(CC) $(CFLAGS) -fsanitize=address -g $(INCLUDES) $(COMMON_SOURCES) $(VALID_SOURCE) $(MLXFLAGS) $(LIBFT) -o $(NAME)

debug_map: $(NAME)
	$(CC) $(CFLAGS) -fsanitize=address -g $(INCLUDES) $(COMMON_SOURCES) $(MAP_SOURCES) C_FILES/11_map_editor.c $(MLXFLAGS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(LIBFTPATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTPATH) fclean

re: fclean all

.PHONY: all clean fclean re obj
