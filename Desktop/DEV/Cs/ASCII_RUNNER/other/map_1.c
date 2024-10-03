#include "_ascii.h"
#include "_header.h"

Grid *gen_map1()
{
  Grid *grid = init_grid();
  reset_text_indexes(grid);
  int c_i = 0;
  init_plrc("player", grid, 0);
  int ground_b_mod = 0;
  int is_GRASS_IC_map = 0;
  int i = 0;
  int cur_ind = 0;
  char *buffer = malloc((map_hei * WIN_X_MAX + map_hei) + 1);
  char *block1 = get_rect(8, 5, ' ', '{', '}', '_', '_');
  char *block2 = get_rect(8, 5, ' ', '{', '}', '_', '_');
  char *stairs1 = get_rect(6, 13, '_', '(', '(', ' ', ' ');

  for (int y = 0; y < map_hei; y++)
  {
    for (int x = 0; x < WIN_X_MAX; x++)
    {
      ground_b_mod = x >= 110 && x <= 140 ? 3 : 0;
      if (y >= GROUND_X + 7 && ((x > 80 && x < 100) || (x > 30 && x < 40)))
      {
        if (y == GROUND_X + 7)
          buffer[i++] = COL_HOR_IC;

        else
          buffer[i++] = rand() % 3 == 0 ? '~' : ' ';
      }
      else if (y == GROUND_X + 7 && x > 30 && x < 40)
        buffer[i++] = '~';
      else if ((y == GROUND_X + ground_b_mod) &&
               (x <= 30 || (x >= 40 && x <= 80) || x >= 100))
      {
        if (y == GROUND_X + ground_b_mod)
        {

          if (x == 51 || x == 53)
            buffer[i++] = COL_VERT_IC;

          else if (!is_GRASS_IC_map)
          {
            if (rand() % 10 == 0)
              is_GRASS_IC_map = rand() % 5 + 3;
            buffer[i++] = COL_HOR_IC;
          }
          else
          {
            buffer[i++] = '/';
            is_GRASS_IC_map--;
          }
        }
      }
      else if (y == GROUND_X + ground_b_mod + 1)
      {
        if (x == 30 || x == 80)
          buffer[i++] = '\\';
        else if (x == 40 || x == 100)
          buffer[i++] = '/';

        else if ((x > 0 && x < 30) || (x > 40 && x < 80) || x > 140)
        {
          if (rand() % 4 == 0)
            buffer[i++] = '-';
          else
            buffer[i++] = ' ';
        }
        else
          buffer[i++] = ' ';
      }
      else
      {
        if ((y == GROUND_X + 1 && (x == 110)) ||
            (y == GROUND_X + 2 && (x == 111)))
          buffer[i++] = '\\';
        else if ((y == GROUND_X + 1 && (x == 140)) ||
                 (y == GROUND_X + 2 && (x == 139)) ||
                 (y == GROUND_X + 2 && (x == 138)))
          buffer[i++] = '/';
        else if (y == GROUND_X + 1 && y <= GROUND_X + ground_b_mod &&
                 (x == 110 || x == 140))
          buffer[i++] = COL_VERT_IC;
        else if (x < 30 || (x > 40 && x < 80) || (x > 100))
        {
          if (y >= GROUND_X + ground_b_mod + 2)
            buffer[i++] = '-';
          else
            buffer[i++] = ' ';
        }
        else if (y >= GROUND_X &&
                 (x == 30 || x == 40 || x == 80 || x == 100))
          buffer[i++] = COL_VERT_IC;
        else if (y == GROUND_X + ground_b_mod + 1 ||
                 y == GROUND_X + ground_b_mod)
          buffer[i++] = COL_HOR_IC;
        else
          buffer[i++] = ' ';
      }
    }
    buffer[i++] = '\n';
  }
  while (i < (map_hei * WIN_X_MAX + map_hei) + 1)
    buffer[i++] = '\0';

  int r_mob = rand_range(7, 11);
  int r_npc = rand_range(1, 3);
  int mob_x_pos = 80;

  for (int m = 0; m < r_mob; m++)
  {
    init_mob("mob", grid, mob_x_pos, GROUND_X - 4, -1, 0);
    mob_x_pos += rand_range(mob_min_dist, mob_max_dist);
  }

  for (int m = 0; m < r_npc; m++)
  {
    char *buff;
    int r = rand() % 4;
    buff = r == 0   ? plr_idle_up
           : r == 1 ? plr_idle_left
           : r == 2 ? plr_idle_right
                    : plr_idle_down2;
    set_dynamic_cell("NPC", buff, mob_x_pos, GROUND_X - 4, NPC, grid, -1, 0);
    mob_x_pos += rand_range(mob_min_dist, mob_max_dist);
  }
  set_dynamic_cell("NPC", plr_idle_right, 90, 75, NPC, grid, -1, 0);
  set_dynamic_cell("NPC", plr_idle_up, 49, 86, NPC, grid, -1, 0);

  mob_x_pos = 30;
  for (int x = 0; x < 15; x++)
  {
    char *top = get_rect(15, 2, ' ', '[', ']', '-', '-');
    cur_ind =
        set_dynamic_cell("BOX", top, mob_x_pos, GROUND_X - 5, env, grid, -1, 0);
    if (cur_ind != -1)
      add_to_grid(grid->cells[cur_ind], buffer);
    c_i++;
    mob_x_pos += 30;
  }
  cur_ind =
      set_dynamic_cell("TREE", tree1, 10, GROUND_X - 10, env, grid, 30, 0);
  if (cur_ind != -1)
    add_to_grid(grid->cells[cur_ind], buffer);
  cur_ind =
      set_dynamic_cell("TREE", tree1, 10, GROUND_X - 10, env, grid, -1, 0);
  if (cur_ind != -1)
    add_to_grid(grid->cells[cur_ind], buffer);

  cur_ind = init_weather(grid, buffer);
  // add_env(grid, buffer);

  free(block1);
  free(block2);
  free(stairs1);

  grid->txt = buffer;

  return (grid);
}
