GAME_NAME = so_long
GAME_SOURCE = C_FILES/so_long.c
BONUS_SOURCE = BONUS/so_long.c

EDITOR_NAME = editor
EDITOR_SOURCES = C_FILES/old_stuff/*.c

MAP_MAKER_NAME = rmap
MAP_MAKER_SOURCES = C_FILES/MAKEMAP.c

UTIL_SOURCES = \
C_FILES/utils/8_delete.c C_FILES/utils/11_get_next_line.c C_FILES/utils/15_map_parser.c C_FILES/utils/2_update_player.c \
C_FILES/utils/14_map_generator.c C_FILES/utils/5_input.c C_FILES/utils/1_init.c C_FILES/utils/10_Vectors.c \
C_FILES/utils/6_mouse.c C_FILES/utils/6_tools.c C_FILES/utils/9_entities.c C_FILES/utils/8_collisions.c \
C_FILES/utils/7_movement.c C_FILES/utils/4_images.c C_FILES/utils/2_update_env.c C_FILES/utils/13_map_checker2.c \
C_FILES/utils/3_render.c C_FILES/utils/12_map_checker.c C_FILES/utils/0_level_loader.c C_FILES/utils/7_colors.c C_FILES/utils/16_audio.c \
C_FILES/utils/2_update_collectibles.c C_FILES/utils/3_entity_tools.c C_FILES/utils/1_init_frames.c

UTIL_BONUS_SOURCES = \
BONUS/utils/8_delete.c BONUS/utils/11_get_next_line.c BONUS/utils/15_map_parser.c BONUS/utils/2_update_player.c \
BONUS/utils/14_map_generator.c BONUS/utils/5_input.c BONUS/utils/1_init.c BONUS/utils/10_Vectors.c \
BONUS/utils/6_mouse.c BONUS/utils/6_tools.c BONUS/utils/9_entities.c BONUS/utils/8_collisions.c \
BONUS/utils/7_movement.c BONUS/utils/4_images.c BONUS/utils/2_update_env.c BONUS/utils/13_map_checker2.c \
BONUS/utils/3_render.c BONUS/utils/12_map_checker.c BONUS/utils/0_level_loader.c BONUS/utils/7_colors.c BONUS/utils/16_audio.c \
BONUS/utils/2_update_collectibles.c BONUS/utils/3_entity_tools.c BONUS/utils/1_init_frames.c

INCLUDES = -I mlx -I libft
MLXFLAGS = -L mlx -lmlx -framework OpenGL -framework AppKit -lz

LIBFTPATH = libft/
LIBFT = $(LIBFTPATH)libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

FSAN = -fsanitize=address -g


$(GAME_NAME): $(LIBFT)
	$(CC) $(CFLAGS)  $(GAME_SOURCE) $(UTIL_SOURCES) $(INCLUDES) $(MLXFLAGS) $(LIBFT) -o $(GAME_NAME)

bonus: $(GAME_NAME)
	$(CC) $(CFLAGS) $(BONUS_SOURCE) $(UTIL_BONUS_SOURCES) $(INCLUDES) $(MLXFLAGS) $(LIBFT) -o $(GAME_NAME)

all: $(GAME_NAME) 

$(LIBFT):
	make -C $(LIBFTPATH)

debug:
	$(CC) $(FSAN) $(GAME_SOURCE) $(UTIL_SOURCES) $(INCLUDES) $(MLXFLAGS) $(LIBFT) -o $(GAME_NAME)

map: all
	$(CC) $(MAP_MAKER_SOURCES) $(UTIL_SOURCES) $(INCLUDES) $(MLXFLAGS) $(LIBFT) -o $(MAP_MAKER_NAME)

game:
	$(CC) $(GAME_SOURCES) $(UTIL_SOURCES) $(INCLUDES) $(MLXFLAGS) $(LIBFT) -o $(GAME_NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(GAME_NAME)
	rm -f $(EDITOR_NAME)
	make -C $(LIBFTPATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTPATH) fclean

re: fclean all

.PHONY: all clean fclean re obj
