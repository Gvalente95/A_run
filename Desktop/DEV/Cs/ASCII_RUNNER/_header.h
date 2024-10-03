#ifndef HEADER
#define HEADER .H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

extern const char *CELL_NAMES[];
extern const char *DIR_NAMES[];
extern const char *ACTION_NAMES[];

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// DEBUG
#define DEB_GRID_CONTENT_SIZE 25

// |    PARAM    |
#define WIN_Y_MAX 60
#define WIN_X_MAX 300
#define CELL_BUFFER 500
#define GROUND_X WIN_Y_MAX / 2
#define SKY_X WIN_Y_MAX + 1
#define REF_SPEED .01f
#define DEBUG_VIEW 0
// VIEW
#define CAM_X_MAX WIN_X_MAX - WIN_X_MAX / 3
#define CAM_X_MAX_MIN WIN_X_MAX / 3
#define CAM_START_X 200
#define CAM_START_Y 0
#define CROP_X 30
#define CROP_Y 0

// METEO
#define STAR_BUFFER 50
#define MET_FREQ 50
#define MET_SPD 2
#define STAR_DUR 50
#define RAIN_DUR 200
#define WEATH_CHNG_SPEED 1
#define SKY_BUFFER 50
#define LIANE_CHANCE 5
#define WIND_DIR 0
#define NO_WEATH_DUR 500

// PLAYER
#define PLR_START_X WIN_X_MAX / 2
#define PLR_START_Y WIN_Y_MAX / 2
#define PLR_SPEED 1
#define PLR_DASH_DURATION 15
#define PLR_DASH_CD 100
#define PLR_JUMP_DURATION 17
#define PLR_MV_HOR 0
#define PLR_MV_VER 0
#define SPELL_CD 5
#define SPELL_DIST 5

// ICONS
#define DEBUG_VIEW_K 'v'
#define COL_VERT_IC '|'
#define COL_HOR_IC '_'
#define COL_STAIR_IC '-'
#define RAND_IC '?'
#define VER_IGN_IC '&'
#define PRJ_LEFT 'p'
#define PRJ_RIGHT 'b'
#define GR_TOP_IC 't'
#define GR_INT_IC 'G'
#define LIANE_START 'S'
#define LIANE1 '`'
#define LIANE2 'L'
#define LIANE_END_ic 'E'

#define SNOW_IC 's'
#define STAR_IC 's'
#define GRASS_IC 'g'
#define RAIN_IC 'R'
#define RAINSPL_IC 'r'

#define DEB_GRID_KEY 'p'
#define UP_K 'w'
#define LEFT_K 'a'
#define DOWN_K 's'
#define RIGHT_K 'd'

#define CROUCH_K 'x'
#define JUMP_K ' '
#define THUND_K 'k'
#define FIRE_K 'f'
#define SHOT_K 't'
#define WATER_K 'b'
#define READ_K 'l'

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

#define FULL_BLOCK "\u25A0"
#define BLACK_SQUARE "\u25FC"
#define WHITE_SQUARE "\u25FB"
#define LIGHT_SHADE "\u2591"
#define MEDIUM_SHADE "\u2592"
#define DARK_SHADE "\u2593"

typedef enum
{
  up,
  up_left,
  up_right,
  down,
  down_left,
  down_right,
  left,
  right,
  none
} directions;

typedef enum
{
  player,
  NPC,
  mob0,
  mob1,
  env,
  ground,
  background,
  coin,
  food,
  empty,
  null
} cell_type;

typedef enum
{
  rainy,
  snowy,
  meteory,
  windy,
  sunny,
} weather;

typedef enum
{
  idle,
  walk,
  run,
  dash,
  jump,
  db_jump,
  land,
  fly,
  fall,
  spell_cast,
  attack,
} cell_action;

typedef enum
{
  in_game,
  paused,
  death,
  end_screen
} Game_state;

typedef struct Cell {
  char *name;
  cell_type c_type;
  cell_type next_c_type;
  cell_action c_action;
  directions dir;
  char *text;
  int x_pos;
  int y_pos;
  int start_x;
  int start_y;
  int width;
  int height;
  int index;
  char p_dir;
  int layer;
  int buff_index;
  int tick;
  int life_tick;
  int jump_time;
  int dash_time;
  int scroll_speed;
  int should_loop;
  int has_db_jmp;
  int mv_up_ok;
  int mv_left_ok;
  int mv_down_ok;
  int mv_right_ok;
} Cell;

typedef struct Sky_c {
  directions dir;
  int index;
  int lifetime;
  char c;
} Sky_c;

typedef struct Camera {
  int x_pos;
  int y_pos;
  int right_brd;
  int left_brd;
  int top_brd;
  int down_brd;
} Cam;

typedef struct Game {
  Cam cam;
  Game_state game_state;
  useconds_t sleep_time;
  weather cur_weather;
  int weather_intensity;
  int is_switching_weather;

  int view_col;
  int x_cam;
  int y_cam;
  int time;
  int score;
  int input;
  int prev_input;
  int prev_move;
  int spell_cd;
} Game;

typedef struct Grid {
  struct Sky_c *sky_c;
  struct Cell *cells;
  struct Cell *plrc;
  int *stars;
  char *txt;
  int rain_am;
  int star_am;
  int map_x_size;
  int map_y_size;
  int cells_amnt;
  int coins;
  int *cloud_positions;
  int has_weapon;
  int mun;
  int b_mun;
  int player_ind;
  int player_hurt;
} Grid;

typedef struct mini_cell {
  char *text;
  char *start_text;
  int index;
  int st_index;
} mini_cell;

// HELPER TOOLS
void set_nonblocking_mode(int enable);
char *get_rect(int width, int height, char interior, char interior2, char brd_left,
               char brd_right, char brd_up, char brd_down);
int is_spell_key(char key);
int is_move_key(char key);
int rand_range(int min, int max);
int get_width(char *buff);
int get_height(char *buff);
char *fit_to_window(char *text);
int get_win_y();
int get_win_x();

// DEBUG & MENUS
int print_start_menu();
void print_colored_text(char *c, char cc, char *color);
void print_grid_debug(Grid *grid, int page);
void print_debug_log(Grid grid, Game game, useconds_t sec);
int print_end_menu(Grid grid, Game game);

// ACTIONS
char *draw_spell(Grid *grid, Game *game);

// MAP GRID AND CELLS
Grid *gen_map1();
Grid *init_grid();
void update_grid(Grid *grid, int speed);
int print_on_grid(char *src, char *dst, int x_pos, int y_pos, int loop);
void print_grid(Grid grid, Game game, int x_crop, int y_crop, char background);
void print_unicode_block(char *color, char *block_char);
int erase(char *dst, int x_pos, int y_pos, int x_len, int y_len, char *dont_erase);
int is_in_string(char c, char *sep);
void noisify(char *dst, int noise_chance, int neigh_chance, char *avoid);

// CELLS
void set_cell(char *name, cell_type type, cell_type nxt_type, Cell *c,
              char *content, int p_dir, char dir, int tick, int life_tick,
              int width, int height, int x_pos, int y_pos, int scroll_speed);
int init_plrc(char *name, Grid *grid, int index);
int init_mob(char *name, Grid *grid, int x_pos, int y_pos, int index, int scroll_speed);
int init_weather(Grid *grid, char *map);
int set_dynamic_cell(char *name, char *content, int x_pos, int y_pos,
                     cell_type type, Grid *grid, int index, int scroll_speed, int should_loop);
void set_empty_cell(Cell *cell);
int add_to_grid(Cell cell, char *map);
void check_colliders(Grid *grid, char *map, int win_x, int show_col);
void erase_cell(Grid *grid, int index);
int get_free_index(Grid grid);
int is_cell_at_index(Cell cell, int x_pos, int y_pos);
void set_sky(Sky_c *c, char icon, directions dir, int lifetime);

#endif