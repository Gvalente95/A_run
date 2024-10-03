#include "_ascii.h"
#include "_header.h"

char *draw_spell(Grid *grid, Game *game)
{
  int input = game->input;
  int x_pos = grid->plrc->x_pos;
  int y_pos = grid->plrc->y_pos;
  int sky_cellt_pos = 0;
  int index = 0;
  char *map = grid->txt;
  directions dir = grid->plrc->dir;

  int is_shift = 0;
  if (input + 32 >= 'A' && input + 32 <= 'Z')
  {
    is_shift = 1;
    input -= 32;
  }

  game->spell_cd += input == FIRE_K    ? SPELL_CD
                    : input == THUND_K ? SPELL_CD
                                       : SPELL_CD;
  switch (input)
  {
  case (THUND_K):
    sky_cellt_pos = x_pos + SPELL_DIST;
    if (sky_cellt_pos < 0)
      sky_cellt_pos = x_pos;
    if (dir == right)
      map[sky_cellt_pos] = 'f';
    else if (dir == left && sky_cellt_pos - (SPELL_DIST * 2) > 0)
      map[sky_cellt_pos - (SPELL_DIST * 2)] = 'f';
    else if (dir == up || dir == down)
      map[sky_cellt_pos - (SPELL_DIST)] = 'f';
    if (is_shift)
    {
      for (int x = -4; x < 9; x++)
      {
        index = sky_cellt_pos - (x * 2);
        if (map[index] && map[index] == ' ')
          map[index] = 'f';
      }
    }
    break;
  case (FIRE_K): {
    if (dir == right)
      index = (WIN_X_MAX + 1) * (y_pos + 2) + x_pos + 10;
    else if (dir == left)
      index = (WIN_X_MAX + 1) * (y_pos + 2) + x_pos - 6;
    else if (dir == up)
      index = (WIN_X_MAX + 1) * (y_pos - 2) + x_pos;
    if (map[index])
      map[index] = 'x';
    if (map[index + 3 - WIN_X_MAX - 1])
      map[index + 3 - WIN_X_MAX - 1] = 'x';
    if (is_shift)
    {
      int displ = 8;
      for (int x = 1; x < 15; x++)
      {
        displ--;
        int ind = index + (x * displ) - WIN_X_MAX * x;
        if (dir == left)
          ind = index - (x * displ) - WIN_X_MAX * x;
        if (map[ind] && map[ind] == ' ')
          map[ind] = 'x';
      }
    }
  }
  break;
  case (SHOT_K): {
    int index = 0;
    if (dir == right)
      index = (WIN_X_MAX + 1) * (y_pos + 2) + x_pos + 8;
    else if (dir == left)
      index = (WIN_X_MAX + 1) * (y_pos + 2) + x_pos - 6;
    else if (dir == up)
      index = (WIN_X_MAX + 1) * (y_pos - 2) + x_pos;
    if (map[index])
      map[index] = dir == right ? '>' : dir == left ? '<'
                                                    : '^';
  }
  break;
  }
  return (dir == left    ? plr_spell_left
          : dir == right ? plr_spell_right
                         : plr_spell_up);
}

int is_spell_key(char key)
{
  char good_cars[] = {FIRE_K, THUND_K, WATER_K, SHOT_K, '\0'};
  int i = 0;
  while (good_cars[i])
  {
    if (key == good_cars[i] || key + 32 == good_cars[i])
      return (1);
    i++;
  }
  return (0);
}
int is_move_key(char key)
{
  if (key == 'd' || key == 'a' || key == 'w' || key == 's' || key == 'x')
    return (1);
  return (0);
}

void check_colliders(Grid *grid, char *map, int win_x, int show_col)
{
  int player_ind =
      (grid->plrc->x_pos + ((grid->plrc->y_pos) * win_x) +
       grid->plrc->y_pos);

  int left_ind[5];
  int right_ind[5];
  int up_ind[5];
  int down_ind[5];

  int up_col_found = 0;
  int left_col_found = 0;
  int right_col_found = 0;
  int down_col_found = 0;
  int map_size = strlen(map);

  for (int x = 0; x < 5; x++)
  {
    left_ind[x] = player_ind + (win_x + 1) * x;
    right_ind[x] = left_ind[x] + grid->plrc->width - 1;
    up_ind[x] = player_ind - win_x + x;
    down_ind[x] =
        up_ind[x] + ((win_x + 1)) + (win_x + 1) * (grid->plrc->height);

    if (left_ind[x] > 0 && left_ind[x] < map_size)
    {
      if (map[left_ind[x]] == '|')
        left_col_found++;
      else if (show_col)
        map[left_ind[x]] = 'a';
    }
    if (right_ind[x] > 0 && right_ind[x] < map_size)
    {
      if (map[right_ind[x]] == '|')
        right_col_found++;
      else if (show_col)
        map[right_ind[x]] = 'd';
    }
    if (up_ind[x] > 0 && up_ind[x] < map_size)
    {
      if (map[up_ind[x]] != ' ')
        up_col_found++;
      else if (show_col)
        map[up_ind[x]] = 'w';
    }
    if (down_ind[x] > 0 && down_ind[x] < map_size)
    {
      if (map[down_ind[x]] == '_' || map[down_ind[x]] == GRASS_IC)
        down_col_found++;
      else if (show_col)
        map[down_ind[x]] = 'v';
    }
  }
  // INSIDE CHAR
  for (int y = 0; y < 5; y++)
  {
    for (int x = 0; x < 5; x++)
    {
      int index = ((y + grid->plrc->y_pos) * (win_x + 1) + x) + grid->plrc->x_pos;
      if (index <= 0 || index > map_size) continue;
      if (map[index] == 'T' || map[index] == 'R')
      {
        grid->plrc->x_pos--;
        // grid->plrc->y_pos += rand() % 2 == 0 ? -1 : 1;
        grid->plrc->y_pos--;
      }
      if (map[index] == 'c')
      {
        grid->plrc->x_pos--;
      }
    }
  }

  (void)up_col_found;

  grid->plrc->mv_down_ok = !down_col_found;
  grid->plrc->mv_up_ok = 1;
  grid->plrc->mv_right_ok = right_col_found <= 0;
  grid->plrc->mv_left_ok = left_col_found <= 0;
}