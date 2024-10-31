#ifndef HEADER_H
# define HEADER_H

#include "ascii.h"
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

// AUDIO
#define AU_bg_world "audio_files/music/bg_world.mp3"
#define AU_bg_house "audio_files/music/bg_house.mp3"
#define AU_bg_fight "audio_files/music/bg_fight.mp3"
#define AU_ship_mv "audio_files/fx/ship_drive.mp3"

#define AU_click1 "audio_files/UI/click1.mp3"
#define AU_click2 "audio_files/UI/click2.mp3"
#define AU_change_sel "audio_files/UI/change_sel.mp3"
#define AU_proj1 "audio_files/UI/proj1.mp3"
#define AU_high_pitch "audio_files/UI/high_pitch.mp3"
#define AU_high_pitch2 "audio_files/UI/high_pitch2.mp3"
#define AU_expl1 "audio_files/fx/expl1.mp3"
#define AU_expl2 "audio_files/fx/expl2.mp3"
#define AU_expl3 "audio_files/fx/expl3.mp3"
#define AU_expl4 "audio_files/fx/expl4.mp3"
#define AU_hurt1 "audio_files/fx/hurt1.mp3"
#define AU_hurt2 "audio_files/fx/hurt2.mp3"
#define AU_hurt3 "audio_files/fx/hurt3.mp3"
#define AU_hurt4 "audio_files/fx/hurt4.mp3"
#define AU_hurt5 "audio_files/fx/hurt5.mp3"
#define AU_thump "audio_files/fx/thump.mp3"

#define AU_ft1 "audio_files/footsteps/FT_Grass_1.wav"
#define AU_ft2 "audio_files/footsteps/FT_Grass_2.wav"
#define AU_ft3 "audio_files/footsteps/FT_Grass_3.wav"
#define AU_ft4 "audio_files/footsteps/FT_Grass_4.wav"
#define AU_ft5 "audio_files/footsteps/FT_Grass_5.wav"
#define AU_ft6 "audio_files/footsteps/FT_Grass_6.wav"
#define AU_ft7 "audio_files/footsteps/FT_Grass_7.wav"

// COLORS
#define RED "\033[31m"
#define BRIGHT_RED "\033[91m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define LIGHT_BLUE "\033[38;5;117m"
#define DIM_WHITE "\033[38;5;250m"
#define PALE_YELLOW "\033[38;5;229m"
#define SOFT_BLUE "\033[38;5;153m"

#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define ORANGE "\033[38;5;214m"
#define BROWN "\033[38;5;94m"
#define DARK_GREEN "\033[38;5;22m"

#define REFRES_SPEED 50000
#define SCRN_MAX_W 250
#define SCRN_MAX_H (SCRN_MAX_W / 3)

#define SCREEN_SIZE (SCRN_MAX_W + (SCRN_MAX_H * SCRN_MAX_W + 1))
#define MAX_CONTENT SCRN_MAX_W * SCRN_MAX_H
#define GRASS_AMNT 0
#define TREES_MAX 20
#define CLOUDS_MAX 2

extern int SCRN_WIDTH;
extern int SCRN_HEIGHT;

#define MOVE_AMOUNT 100000
#define JMP_AMOUNT 4
#define TERRAIN_AMNT 200
#define HOUSE_AMNT 50
#define MOBS_AMOUNT 200
#define SPIDER_AMOUNT 200
#define BOSS_AMNT 10

#define PROJ_AMOUNT 100

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a < b ? a : b))
#define MINMAX(a, b, c) ()

#define HOR_COL 'Z'
#define VER_COL 'Y'
#define INV_HOR_COL 'y'
#define INV_VER_COL 'A'

#define COL_CHECKL '!'

#define GRN_GRASS '}'
#define ORNG_GRASS '{'
#define RED_GRASSS '&'

#define PROJ_IC 'K'
#define LEAF_IC 'L'

#define GRASS_IC 'L'
#define MUD_IC 'x'
#define ICE_IC '^'
#define WATER_IC '~'

#define GRAB_K 'g'
#define DROP_K 'd'
#define SHOOT_K ' '
#define CHNG_WEAP 'e'

#define RIFLE_PUSH 4
#define WEAP_AMNT 3

typedef enum ACTION {idle, move, attack, jump, falling, death, ACTION_TYPE_COUNT} ACTION;
typedef enum TERRAIN_TYPE {grass_field, ice_field, lake, swamp, TERRAIN_TYPE_COUNT} TERRAIN_TYPE;
typedef enum WEAPONS_TYPES {rifle, sword, bomb, WEAPONS_TYPES_COUNT} WEAPONS_TYPES;
typedef enum HOUSE_TYPES {merchant, house, dungeon, HOUSE_TYPES_COUNT} HOUSE_TYPES;
typedef enum DIRECTION {down, left, right, up} DIRECTION;

extern const char *HOUSE_TYPES_LB[50];

typedef struct s_WEAPON
{
	WEAPONS_TYPES weap;
	int x_pos, y_pos, pow, reload, speed, mun, start_mun, active;
	char gfx[4][2][500];
	char color[20];
	char label[20];
} WEAPON;

typedef struct BULLET
{
	int speed;
	char *color;
} BULLET;

typedef struct TERRAIN
{
	char content;
	char frame[MAX_CONTENT];
	TERRAIN_TYPE type;
	int size[2];
	int pos[2];
} TERRAIN;

typedef struct s_ENTITY
{
	DIRECTION 	dir;
	ACTION 		action;
	WEAPON 		weap;
	int		position[2], movement[2], prev_movement[2];
	int		width, height, jumps, hp, maxHP, speed, hurt;
	char	frame[MAX_CONTENT];
	char	idle[4][MAX_CONTENT];
	char	move[4][2][MAX_CONTENT];
	char	attack[4][MAX_CONTENT];
	char	jump[4][MAX_CONTENT];
	char	falling[4][MAX_CONTENT];
	char	sleep[4][MAX_CONTENT];
	char	death[4][MAX_CONTENT];
	char	label[100];
}	ENTITY;

typedef struct s_house
{
	char		frame[MAX_CONTENT];
	char		interior[MAX_CONTENT];

	int 		position[2];
	int			index;
	int 		size[2];
	int 		intr_size[2];
	char 		label[50];
	HOUSE_TYPES type;
	ENTITY		occupants[10];
}	HOUSE;

extern ENTITY PLAYER;
extern ENTITY MOBS[MOBS_AMOUNT];
extern ENTITY BOSS[BOSS_AMNT];
extern ENTITY SPIDERS[SPIDER_AMOUNT];
extern WEAPON WEAPONS[3];
extern HOUSE houses[HOUSE_AMNT];
extern HOUSE screen_houses[HOUSE_AMNT];

extern int 	game_time;
extern char screen[];
extern char prvscrn[];
extern int	projectiles[100][4];
extern int	WEAPON_INDEX;
extern int	PROJ_FIRED;
extern int 	INV_FRAME;
extern int	DEBUG_CHECK;
extern int	PLAYER_HOUSE;
#define DIRT_AMNT 10

extern int	input;
extern int	prev_input;
extern int	movement[2];
extern int	scroll[2];
extern int	grass[GRASS_AMNT][2];
extern int	trees[TREES_MAX][2];
extern int	clouds[CLOUDS_MAX][2];
extern struct TERRAIN terrains[TERRAIN_AMNT];

//	TOOLS
void 	set_nonblocking_mode(int enable);
int 	rand_range(int min, int max);
int 	get_height(const char *canv);
int		get_width(const char *canv);

//	AUDIO
pid_t 	play_sound(const char *filename, int loop);
void 	stop_sound(pid_t pid);
int 	is_playing(pid_t pid);

//	LOOP
void	init_game();
int 	update_game();
int 	check_crop();
void	render_env();
void 	print_colored_text(char *c, char cc, char *color);
int 	is_in_canv(int x, int y, char *src, char *dst);

//	RENDER
int 	render_game();
void	render_houses();
char	*get_cropped_str(const char *ref, int height, int below_x, int after_x);
int		print_entity(ENTITY elem, char *dst);
int		print_string(char *src, char *dst, int x_start, int y_start);

//	BUILDINGS
char	*get_rect(char canv[], int width, int height, char interior, int exterior);
char	*get_triangle(char *canv, int width, int height, char interior, int exterior);
char 	*get_house(char *canv, int width, int height, char interior, int exterior, HOUSE_TYPES type);
char 	*get_house_interior(char *canv, int width, int height, char interior, int exterior, HOUSE_TYPES type);

#endif