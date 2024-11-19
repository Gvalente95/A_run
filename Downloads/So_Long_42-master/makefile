# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Binary names
GAME_NAME = so_long
BONUS_NAME = bonus
EDITOR_NAME = editor
MAP_MAKER_NAME = rmap

# Source files
GAME_SOURCE = C_FILES/so_long.c
BONUS_SOURCE = BONUS_FILES/so_long.c
EDITOR_SOURCE = BONUS_FILES/map_editor.c
MAP_MAKER_SOURCE = BONUS_FILES/makemap.c

UTIL_SOURCES = \
C_FILES/utils/11_get_next_line.c C_FILES/utils/15_map_parser.c C_FILES/utils/2_update_player.c C_FILES/utils/14_map_generator.c \
C_FILES/utils/5_input.c C_FILES/utils/1_init.c C_FILES/utils/10_Vectors.c C_FILES/utils/8_collisions.c \
C_FILES/utils/4_images.c C_FILES/utils/13_map_checker2.c C_FILES/utils/1_init_frames.c C_FILES/utils/3_render.c \
C_FILES/utils/12_map_checker.c C_FILES/utils/18_free_md.c

UTIL_BONUS_SOURCES = \
BONUS_FILES/utils/17_audio.c BONUS_FILES/utils/0_tileset_mapper.c BONUS_FILES/utils/11_get_next_line.c \
BONUS_FILES/utils/15_map_parser.c BONUS_FILES/utils/2_update_player.c BONUS_FILES/utils/14_map_generator.c \
BONUS_FILES/utils/5_input.c BONUS_FILES/utils/8_delete.c BONUS_FILES/utils/3_entity_tools.c BONUS_FILES/utils/1_init.c \
BONUS_FILES/utils/10_Vectors.c BONUS_FILES/utils/16_editor_utils.c BONUS_FILES/utils/6_mouse.c BONUS_FILES/utils/0_level_loader.c \
BONUS_FILES/utils/6_tools.c BONUS_FILES/utils/7_colors.c BONUS_FILES/utils/9_entities.c BONUS_FILES/utils/8_collisions.c \
BONUS_FILES/utils/16_save_map.c BONUS_FILES/utils/16_update_editor.c BONUS_FILES/utils/7_movement.c BONUS_FILES/utils/4_images.c \
BONUS_FILES/utils/2_update_env.c BONUS_FILES/utils/13_map_checker2.c BONUS_FILES/utils/16_load_editor_images.c \
BONUS_FILES/utils/1_init_frames.c BONUS_FILES/utils/2_update_collectibles.c BONUS_FILES/utils/3_render.c \
BONUS_FILES/utils/12_map_checker.c BONUS_FILES/utils/18_free_md.c

# Includes and libraries
INCLUDES = -I mlx -I libft
MLXFLAGS = -L mlx -lmlx -framework OpenGL -framework AppKit -lz

LIBFTPATH = libft/
LIBFT = $(LIBFTPATH)libft.a

# Targets
all: $(GAME_NAME)

$(GAME_NAME): $(GAME_SOURCE) $(UTIL_SOURCES) $(LIBFT)
	$(CC) $(CFLAGS) $(GAME_SOURCE) $(UTIL_SOURCES) $(INCLUDES) $(MLXFLAGS) $(LIBFT) -o $(GAME_NAME)

$(BONUS_NAME): $(BONUS_SOURCE) $(UTIL_BONUS_SOURCES) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_SOURCE) $(UTIL_BONUS_SOURCES) $(INCLUDES) $(MLXFLAGS) $(LIBFT) -o $(BONUS_NAME)

$(EDITOR_NAME): $(EDITOR_SOURCE) $(UTIL_BONUS_SOURCES) $(LIBFT)
	$(CC) $(CFLAGS) $(EDITOR_SOURCE) $(UTIL_BONUS_SOURCES) $(INCLUDES) $(MLXFLAGS) $(LIBFT) -o $(EDITOR_NAME)

$(MAP_MAKER_NAME): $(LIBFT)
	$(CC) $(CFLAGS) $(MAP_MAKER_SOURCE) $(UTIL_BONUS_SOURCES) $(INCLUDES) $(MLXFLAGS) $(LIBFT) -o $(MAP_MAKER_NAME)

$(LIBFT):
	make -C $(LIBFTPATH)

debug: $(LIBFT)
	$(CC) $(CFLAGS) -fsanitize=address -g $(GAME_SOURCE) $(UTIL_SOURCES) $(INCLUDES) $(MLXFLAGS) $(LIBFT) -o $(GAME_NAME)

debug_bonus: $(LIBFT)
	$(CC) $(CFLAGS) -fsanitize=address -g $(BONUS_SOURCE) $(UTIL_BONUS_SOURCES) $(INCLUDES) $(MLXFLAGS) $(LIBFT) -o $(BONUS_NAME)

clean:
	rm -f $(GAME_NAME) $(BONUS_NAME) $(EDITOR_NAME) $(MAP_MAKER_NAME)
	make -C $(LIBFTPATH) clean

fclean: clean
	rm -f $(LIBFT)
	make -C $(LIBFTPATH) fclean

re: fclean all

.PHONY: all clean fclean re
