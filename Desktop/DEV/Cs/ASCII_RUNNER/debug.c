#include "_ascii.h"
#include "_header.h"

void print_grid_debug(Grid *grid, int cur_index)
{
  int i = 0;
  int u = 0;
  system("clear");

  while (grid->cells[i].c_type != empty)
    i++;
  i = cur_index;

  printf("(%d - %d) of %d\n\n\n", cur_index, DEB_GRID_CONTENT_SIZE + cur_index, CELL_BUFFER + 1);
  while (grid->cells[i].c_type != null && i < DEB_GRID_CONTENT_SIZE + cur_index)
  {
    Cell c = grid->cells[i];
    printf("\n");
    printf("%d ", i);
    print_colored_text(c.name, '\0', GREEN);
    printf("    X_Pos	%d	Y_Pos:  %d	WIDTH:	%d	HEIGHT:	"
           "%d	I_BUFFER: %d	type:	%s  loop: %d",
           c.x_pos, c.y_pos, c.width, c.height, c.buff_index, CELL_NAMES[c.c_type], c.should_loop);
    if (i > 1 && grid->cells[i].name == grid->cells[i - 1].name)
    {
      if (grid->cells[i].name != grid->cells[i + 1].name)
        printf("\n______________________________________________________________________________________________________________________________________\n");
      i++;
      continue;
    }
    printf("\n\n");
    u = 0;
    if (grid->cells[i].text != NULL)
    {
      while (grid->cells[i].text[u])
      {
        if (grid->cells[i].text[u] == '\n') printf("\\n");
        printf("%c", c.text[u++]);
      }
    }

    if (u > 1 && grid->cells[i].name != grid->cells[i + 1].name)
      printf("\n______________________________________________________________________________________________________________________________________\n");
    i++;
  }
  printf("\n\n");
}

void print_debug_log(Grid grid, Game game, useconds_t sec)
{
  char c = game.input == ' ' ? '_' : game.input;
  char c_prev = game.prev_input == ' ' ? '_' : game.prev_input;

  printf("INPUTS		PLAYER_POS	CAM		"
         "PLR_type	CDs		GAME\n");
  printf("time: %d	score: %d", game.time, game.score);
  printf("\n");
  printf("cur Input:  %c	x: %d		x: %d       spell_CD: %d\n", c, grid.plrc->x_pos, game.x_cam, game.spell_cd);
  printf("prev input: %c	y: %d		y: %d\n", c_prev, grid.plrc->y_pos, game.y_cam);
  printf("prev move: %c\n", game.prev_move);
  printf("current direction:%s\n", DIR_NAMES[grid.plrc->dir]);
  printf("ACTION:%s\n", ACTION_NAMES[grid.plrc->c_action]);

  printf("MOVEMENTS\n");
  printf("  ^ %d\n", grid.plrc->mv_up_ok);
  printf("< %d  %d >          sl_time: %u\n", grid.plrc->mv_left_ok, grid.plrc->mv_right_ok, sec);
  printf("    %d\n", grid.plrc->mv_down_ok);

  char *weather = game.cur_weather == sunny     ? "sunny"
                  : game.cur_weather == rainy   ? "rainy "
                  : game.cur_weather == meteory ? "meteor_fall"
                  : game.cur_weather == windy   ? "windy"
                  : game.cur_weather == snowy   ? "snowy"
                                                : "not found";
  printf("CUR_WEATHER:%s    WEATH_INTENSITY:%d", weather, game.weather_intensity);

  printf("can double jump: %d  jump time: %d  dash time: %d\n", grid.plrc->has_db_jmp, grid.plrc->jump_time, grid.plrc->dash_time);
}