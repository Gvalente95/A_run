#include "header.h"

const char *HOUSE_TYPES_LB[50] = {"Merchant", "House", "Dungeon"};

char 	screen[SCREEN_SIZE];
char 	prvscrn[SCREEN_SIZE];
ENTITY 	PLAYER;
ENTITY 	MOBS[MOBS_AMOUNT];
ENTITY 	BOSS[BOSS_AMNT];
ENTITY 	SPIDERS[SPIDER_AMOUNT];
ENTITY 	PLATFORMS[10];
WEAPON	WEAPONS[WEAPONS_TYPES_COUNT];
TERRAIN	terrains[TERRAIN_AMNT];
HOUSE 	houses[HOUSE_AMNT];
HOUSE	screen_houses[HOUSE_AMNT];

int		SCRN_WIDTH = SCRN_MAX_W;
int		SCRN_HEIGHT = SCRN_MAX_H;
int		PLAYER_HOUSE = -1;

int		grass[GRASS_AMNT][2];
int		trees[TREES_MAX][2];
int		clouds[CLOUDS_MAX][2];
int		projectiles[100][4];

int		input, prev_input;
int		movement[2];
int		scroll[2];
int		game_time;

int		WEAPON_INDEX = 0;
int		PROJ_FIRED = 0;
int 	INV_FRAME = 0;
int		DEBUG_CHECK = 0;
int		FTSTEP_PLAYED = 0;
const char ft_sounds[7][40] = {AU_ft1, AU_ft2, AU_ft3, AU_ft4, AU_ft5, AU_ft6, AU_ft7};

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	struct winsize w;
	int	is_full_screen = 0;

	screen_houses[0].type = HOUSE_TYPES_COUNT;


	pid_t PRC_bg_audio;
	char roc[MAX_CONTENT];
	get_rect(roc, 20, 20, '#', 1);

	if (argc == 2) DEBUG_CHECK = atoi(argv[1]);

	scroll[0] = scroll[1] = movement[0] = movement[1] = 0;
	init_game();
	game_time = 0;
	PRC_bg_audio = play_sound(AU_bg_house, 1);
	while (1)
	{
		if (input == 'f') is_full_screen = !is_full_screen;
		if (is_full_screen)
		{
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			SCRN_WIDTH = w.ws_col;
			SCRN_HEIGHT = w.ws_row;
		}
		else{
			SCRN_WIDTH = SCRN_MAX_W;
			SCRN_HEIGHT = SCRN_MAX_H;
		}
    	
		if (!is_playing(PRC_bg_audio)) PRC_bg_audio = play_sound(AU_bg_house, 1);
		if (PLAYER.action == move && !FTSTEP_PLAYED)
		{
			play_sound(ft_sounds[rand_range(0, 6)], 0);
			FTSTEP_PLAYED = 1;
		}
		if (FTSTEP_PLAYED) {FTSTEP_PLAYED++; if (FTSTEP_PLAYED > 3) FTSTEP_PLAYED = 0;}
		if (input == 'q') break;
		if (input == ' ') play_sound(AU_change_sel, 0);
		if (input == '1') DEBUG_CHECK = !DEBUG_CHECK;
		get_rect(screen, SCRN_WIDTH, SCRN_HEIGHT, ' ', 1);
		update_game();
		print_string(roc, screen, 5 - scroll[0], SCRN_HEIGHT - 30 - scroll[1]);
		render_game();
		usleep(REFRES_SPEED);
		game_time ++;
	}
	stop_sound(PRC_bg_audio);
	return (0);
}
