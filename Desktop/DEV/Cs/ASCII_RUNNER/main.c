#include "_ascii.h"
#include "_header.h"

useconds_t delay_microseconds = (useconds_t)(REF_SPEED * 2000000);

void set_input(int input, Game *game, Grid *grid)
{
  game->prev_input = game->input;
  game->input = input;

  if (input == ' ' && grid->plrc->mv_up_ok)
  {
    if (grid->plrc->c_action != jump && grid->plrc->mv_up_ok && !grid->plrc->mv_down_ok)
    {
      grid->plrc->c_action = jump;
      grid->plrc->has_db_jmp = 0;
      grid->plrc->jump_time = PLR_JUMP_DURATION;
    }

    else if (!grid->plrc->has_db_jmp && (grid->plrc->c_action == fall || grid->plrc->c_action == jump))
    {
      grid->plrc->has_db_jmp = 1;
      grid->plrc->c_action = db_jump;
      grid->plrc->jump_time = PLR_JUMP_DURATION;
    }
  }
  else if (is_move_key(input) && grid->plrc->dash_time <= 0)
  {
    grid->plrc->c_action = dash;
    grid->plrc->dash_time = PLR_DASH_DURATION + PLR_DASH_CD;
    grid->plrc->dir = input == 'w' ? up : input == 's' ? down
                                      : input == 'a'   ? left
                                                       : right;
    grid->plrc->has_db_jmp = 0;
  }

  else if (is_move_key(input))
  {
    game->prev_move = game->input;
    if (grid->plrc->c_action != jump && grid->plrc->c_action != dash && grid->plrc->c_action != db_jump && grid->plrc->c_action != fall) grid->plrc->c_action = walk;
    if (input == 'w')
    {
      if (grid->plrc->mv_up_ok && PLR_MV_VER)
        grid->plrc->y_pos--;
      if (PLR_MV_VER) grid->plrc->dir = up;
    }
    if (input == 'a')
    {
      if (grid->plrc->mv_left_ok && PLR_MV_HOR)
        grid->plrc->x_pos--;
      if (PLR_MV_HOR) grid->plrc->dir = left;
    }
    if (input == 's')
    {
      if (grid->plrc->mv_down_ok && PLR_MV_VER)
        grid->plrc->x_pos--;
      if (PLR_MV_VER) grid->plrc->dir = down;
    }
    if (input == 'd')
    {
      if (grid->plrc->mv_right_ok && PLR_MV_VER)
        grid->plrc->x_pos++;
      if (PLR_MV_HOR) grid->plrc->dir = right;
    }
  }

  else if (is_spell_key(input) && game->spell_cd == 0)
  {
    grid->plrc->c_action = spell_cast;
    while (game->spell_cd <= 20)
    {
      draw_spell(grid, game);
      game->spell_cd++;
    }
    game->spell_cd = 0;
  }
  else
    grid->plrc->c_action = idle;
}

void handle_no_input(Game game, Grid *grid)
{
  int jmp_time = grid->plrc->jump_time;
  int dash_time = grid->plrc->dash_time;
  cell_action c_a = grid->plrc->c_action;
  directions d = grid->plrc->dir;
  Cell c = *grid->plrc;

  if (dash_time >= 0)
  {
    if (grid->plrc->dash_time <= PLR_DASH_CD)
    {
      if (!PLR_MV_HOR && grid->plrc->dash_time == PLR_DASH_CD)
      {
        grid->plrc->dir = right;
        grid->plrc->c_action = grid->plrc->mv_down_ok ? fall : walk;
      }
    }
    else
    {
      if (d == down || d == up) grid->plrc->x_pos++;

      grid->plrc->y_pos += d == down && c.mv_down_ok ? 1 : d == up && c.mv_up_ok ? -1
                                                                                 : 0;
      grid->plrc->x_pos += d == left && c.mv_left_ok ? -1 : d == right && c.mv_right_ok ? 1
                                                                                        : 0;
      grid->plrc->c_action = dash;
    }

    grid->plrc->dash_time--;
  }

  if (jmp_time >= 0)
  {
    if (((c_a == jump && jmp_time >= PLR_JUMP_DURATION - 10) || (c_a == db_jump && jmp_time >= PLR_JUMP_DURATION - 12)) && grid->plrc->mv_up_ok)
      grid->plrc->y_pos--;
    if (PLR_MV_HOR)
    {
      if (d == right)
        grid->plrc->x_pos++;
      if (d == left)
        grid->plrc->x_pos--;
    }
    grid->plrc->jump_time--;
  }
  else if (grid->plrc->mv_down_ok && grid->plrc->c_action != dash)
  {
    grid->plrc->c_action = fall;
    grid->plrc->y_pos++;
    if (PLR_MV_HOR)
      grid->plrc->x_pos += grid->plrc->dir == right ? 1 : grid->plrc->dir == left ? -1
                                                                                  : 0;
  }
  else if (grid->plrc->c_action == fall)
  {
    grid->plrc->c_action = walk;
    game.input = game.prev_move;
  }

  if (grid->plrc->c_action == fall && !grid->plrc->mv_down_ok)
  {
    grid->plrc->c_action = walk;
    game.input = game.prev_input;
  }
  if (!grid->plrc->mv_right_ok)
    grid->plrc->x_pos--;

  if (grid->plrc->c_action == walk)
    grid->plrc->dash_time = 0;
}

int handle_anim(Cell *c, Game game)
{
  if (game.time % 4 == 0)
    c->buff_index = !c->buff_index;
  directions dir = c->dir;
  char *anim;
  switch (c->c_action)
  {
  case idle:
    anim = dir == up     ? plr_idle_up
           : dir == down ? plr_idle_down1
           : dir == left ? plr_idle_left
                         : plr_idle_right;
    break;
  case walk:
    anim = dir == up      ? c->buff_index ? plr_mv_up2 : plr_mv_up1
           : dir == down  ? c->buff_index ? plr_mv_down2 : plr_mv_down1
           : dir == left  ? c->buff_index ? plr_mv_left2 : plr_mv_left1
           : dir == right ? c->buff_index ? plr_mv_right1 : plr_mv_right2
                          : plr_jmp3;
    break;
  case jump:
  case fall:
    anim = dir == up     ? plr_jmp_up
           : dir == down ? plr_jmp_down
           : dir == left ? plr_jmp_left
                         : plr_jmp_right;
    break;
  case db_jump:
    anim = dir == up     ? plr_djmp_left
           : dir == down ? plr_djmp_left
           : dir == left ? plr_djmp_left
                         : plr_djmp_left;
    break;
  case dash:
  case spell_cast:
    anim = dir == up     ? plr_spell_up
           : dir == down ? plr_spell_down
           : dir == left ? plr_spell_left
                         : plr_spell_right;
    break;
  default:
    anim = plr_jmp2;
  }
  if (c->text != NULL) free(c->text);
  c->text = strdup(anim);

  return (0);
}

void set_grid(Game game, Grid *grid, int win_x, int win_y, int *stars, int show_col)
{
  char *map = get_rect(win_x, win_y, ' ', ' ', '|', '|', ' ', ' ');
  int i = 0;

  for (int i = 0; i < STAR_BUFFER - 1; i++)
  {
    int max_index = win_x + ((win_x + 1) * (win_y - 4));
    if (map[stars[i]] == ' ')
    {
      map[stars[i]] = STAR_IC;
      if (rand() % STAR_DUR == 0)
        stars[i] = rand_range(0, max_index);
    }
    else
    {
      while (i >= win_x + win_y && map[stars[i]] != ' ')
        stars[i] = rand_range(0, max_index);
    }
  }

  while (grid->cells[i].text)
  {
    // IF IS IN SCREEN
    if (grid->cells[i].x_pos < win_x && grid->cells[i].y_pos < win_y && grid->cells[i].x_pos >= -grid->cells[i].width && grid->cells[i].y_pos >= 0)
    {
      if (grid->cells[i].scroll_speed && game.time % grid->cells[i].scroll_speed == 0)
        grid->cells[i].x_pos--;

      if (grid->cells[i].c_type == mob1)
      {
        if (game.time % 2 == 0)
        {
          grid->cells[i].buff_index++;
          if (grid->cells[i].buff_index > 3) grid->cells[i].buff_index = 0;
          grid->cells[i].text = grid->cells[i].buff_index == 0 ? bird1 : grid->cells[i].buff_index == 1 ? bird2
                                                                     : grid->cells[i].buff_index == 2   ? bird3
                                                                     : grid->cells[i].buff_index == 3   ? bird2
                                                                                                        : bird1;
          grid->cells[i].x_pos--;
        }
      }

      add_to_grid(grid->cells[i], map);
    }
    else
    {
      // IF NO LOOP
      if (!grid->cells[i].should_loop)
        erase_cell(grid, i);
      else
      {
        if (grid->cells[i].x_pos <= 0)
        {
          grid->cells[i].x_pos = win_x - 1;
          if (grid->cells[i].c_type == ground)
          {
            int ry = rand_range(-10, 10);
            if (ry + grid->cells[i].height > WIN_Y_MAX)
              ry = ry + grid->cells[i].height;
            else if (ry + +grid->cells[i].height < 0)
              ry = 10;
            grid->cells[i].y_pos += ry;
            if (i < CELL_BUFFER && (grid->cells[i + 1].c_type == env || grid->cells[i + 1].c_type == mob0 || grid->cells[i + 1].c_type == coin))
            {
              grid->cells[i + 1].y_pos += ry;
              grid->cells[i + 1].x_pos = win_x - 1 + rand_range(0, 5);
            }
          }
        }
        grid->cells[i].x_pos--;
      }
    }
    i++;
  }

  check_colliders(grid, map, win_x, show_col);

  int dur = game.weather_intensity > SKY_BUFFER - 1 ? SKY_BUFFER - 1 : game.weather_intensity;

  for (int i = 0; i < dur; i++)
  {
    if (!grid->sky_c[i].c) break;

    grid->sky_c[i].lifetime--;
    // if (game.time % 2 == 1)
    grid->sky_c[i].index += win_x;

    if (grid->sky_c[i].index >= 0 && grid->sky_c[i].index < (win_x * win_y))
    {
      if (grid->sky_c[i].lifetime <= 0 || !map[grid->sky_c[i].index] ||
          (map[grid->sky_c[i].index] != ' ' && !is_in_string(map[grid->sky_c[i].index], "#s.+-")))
      {
        if (grid->sky_c[i].lifetime > 0)
        {
          for (int x = -1; x < 3; x++)
          {
            // Check bounds before modifying map
            if (grid->sky_c[i].index - WIN_X_MAX - 1 + x >= 0 &&
                grid->sky_c[i].index - WIN_X_MAX - 1 + x < win_x * win_y &&
                map[grid->sky_c[i].index - WIN_X_MAX - 1 + x] == ' ')
              map[grid->sky_c[i].index - WIN_X_MAX - 1 + x] = RAINSPL_IC;
          }
        }
        grid->sky_c[i].index = rand_range(0, WIN_X_MAX - 1);
        grid->sky_c[i].lifetime = rand_range(RAIN_DUR / 4, RAIN_DUR);
      }
      else
        map[grid->sky_c[i].index] = RAIN_IC;
    }
    else
    {
      // If index out of bounds, reset it safely
      grid->sky_c[i].index = rand_range(0, WIN_X_MAX - 1);
      grid->sky_c[i].lifetime = rand_range(RAIN_DUR / 4, RAIN_DUR);
    }
  }

  grid->txt = strdup(map);
  free(map);
}

int update_game()
{
  int win_x = WIN_X_MAX;
  int win_y = WIN_Y_MAX;
  int show_col = 0;
  float base_ms = .3f;
  float ms = base_ms;

  int is_in_debug_menu = 0;
  int menu_page = 0;
  int in_pause_menu = 0;
  int has_lost = 0;
  int noise_amnt = 10;
  int is_slow_framing = 0;

  Game game;
  game.spell_cd = 0;
  game.score = 0;
  game.time = 0;
  game.view_col = 0;
  game.cur_weather = rainy;
  game.weather_intensity = 1;
  game.is_switching_weather = 0;
  game.input = 'd';
  game.prev_input = 'd';
  game.prev_move = 'd';

  Cam cam;
  cam.y_pos = 0;
  cam.x_pos = 0;
  cam.down_brd = 20;
  cam.top_brd = 80;
  cam.left_brd = 20;
  cam.right_brd = 20;
  game.cam = cam;

  Grid *grid = init_grid();
  int *stars = malloc(STAR_BUFFER * sizeof(int));
  for (int x = 0; x < STAR_BUFFER; x++)
  {
    stars[x] = rand_range(1, WIN_X_MAX * WIN_Y_MAX);
  }

  int cur_coin = 0;
  int cur_tree = 0;

  // set_dynamic_cell("FAR_MOUN", get_rect(WIN_X_MAX / 3, WIN_Y_MAX / 2, '#', ' ', '.', '.', '.', '.'), WIN_X_MAX - 1, WIN_Y_MAX - WIN_Y_MAX / 2 + 5, env, grid, -1, 5, 1);

  set_dynamic_cell("SUN", sun, 40, 10, background, grid, -1, 0, 1);
  for (int x = 0; x < 600; x += rand_range(40, 80))
    set_dynamic_cell("FAR_CLOUD", cloud_1, x, rand_range(5, 20), background, grid, -1, 4, 1);
  for (int x = 60; x < 600; x += 200)
    set_dynamic_cell("FAR_GROUND", get_rect(rand_range(40, 60), rand_range(2, 13), '\'', ' ', VER_IGN_IC, VER_IGN_IC, '-', '-'), x, WIN_Y_MAX / 2 + rand_range(-10, 10), env, grid, -1, 3, 1);
  for (int x = 0; x < 600; x += rand_range(280, 320))
    set_dynamic_cell("CLOSE_CLOUD", cloud_2, x, rand_range(1, 10), background, grid, -1, 2, 1);
  set_dynamic_cell("long_GRND", get_rect(60, 5, GR_INT_IC, GR_TOP_IC, '|', '|', '_', '_'), WIN_X_MAX / 2 - 10, 36, ground, grid, -1, 1, 0);
  for (int x = WIN_X_MAX / 2 + 70; x < WIN_X_MAX / 2 + 70 + 600; x += 60)
  {
    int i = set_dynamic_cell("CLOSE_GROUND", get_rect(rand_range(30, 45), rand_range(2, 13), GR_INT_IC, GR_TOP_IC, '|', VER_IGN_IC, '_', '_'), x, WIN_Y_MAX / 2 + rand_range(-4, 4), ground, grid, -1, 1, 1);
    Cell c = grid->cells[i];
    if (cur_tree < 2)
    {
      set_dynamic_cell("TREE", tree1, c.x_pos + rand_range(1, c.width - 5), c.y_pos - 10, env, grid, -1, 1, 1);
      cur_tree++;
    }
    else if (cur_coin < 2)
    {
      set_dynamic_cell("COIN", coin_0, c.x_pos + rand_range(1, c.width - 4), c.y_pos - 6, coin, grid, -1, 1, 1);
      cur_coin++;
    }
    else
      set_dynamic_cell("MOB", mob_1_left1, c.x_pos + rand_range(1, c.width - 4), c.y_pos - 4, mob0, grid, -1, 1, 1);
  }
  init_plrc("PLR", grid, -1);
  grid->plrc->dir = right;
  set_dynamic_cell("BIRD", bird1, WIN_X_MAX + 50, WIN_Y_MAX / 2 + rand_range(-5, 5), mob1, grid, -1, 1, 1);
  set_dynamic_cell("BIRD", bird1, WIN_X_MAX + 80, WIN_Y_MAX / 2 + rand_range(-5, 5), mob1, grid, -1, 1, 1);

  while (1)
  {
    useconds_t sleep_time = delay_microseconds * ms;
    usleep(sleep_time);

    if (!has_lost)
    {
      ms -= .00016f;
      if (ms < .01f) ms = .01f;
    }
    else
    {
      while (ms < 5)
      {
        system("clear");
        noise_amnt--;
        game.time++;
        ms += .1;
        if (noise_amnt <= 0) noise_amnt = 1;
      }

      noise_amnt = 20;

      int choice = print_end_menu(*grid, game);
      if (choice == 0)
      {
        system("clear");
        return (0);
      }
      if (choice == 1)
      {
        has_lost = !has_lost;
        grid->plrc->x_pos = win_x / 2;
        set_dynamic_cell("GR_PLAT", get_rect(30, 4, '*', GRASS_IC, '|', '|', '_', '_'), win_x / 2, win_y / 2 - 20 + grid->plrc->height, ground, grid, -1, 1, 0);

        grid->plrc->y_pos = win_y / 2 - 20;
        ms = base_ms;
      }
    }

    set_grid(game, grid, win_x, win_y, stars, show_col);
    print_grid(*grid, game, CROP_X, CROP_Y, ' ');
    printf("\n");
    if (is_in_debug_menu) print_debug_log(*grid, game, sleep_time);

    fd_set readfds;
    struct timeval timeout;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    timeout.tv_sec = 0;
    timeout.tv_usec = delay_microseconds * .1;
    int retv;
    retv = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
    game.time++;
    if (game.time > 6000)
      game.time = 0;

    if (game.weather_intensity > SKY_BUFFER + NO_WEATH_DUR)
      game.is_switching_weather = 1;
    if (game.weather_intensity <= 0)
    {
      game.is_switching_weather = 0;
      game.weather_intensity = 1;
      weather new_weather = game.cur_weather;
      while (new_weather == game.cur_weather)
        new_weather = rand() % 5;
      game.cur_weather = new_weather;
    }
    game.weather_intensity += (game.is_switching_weather ? -1 : 1) * WEATH_CHNG_SPEED;

    if (grid->plrc->x_pos + grid->plrc->width < 30)
      has_lost = 1;

    if (grid->plrc->y_pos < 0)
      grid->plrc->y_pos++;
    if (grid->plrc->y_pos >= WIN_Y_MAX - 1)
      has_lost = 1;

    if (grid->plrc->x_pos < win_x / 2 && grid->plrc->mv_right_ok)
    {
      int distance = abs(grid->plrc->x_pos - win_x / 2);
      int frequency = max(1, 11 - min(10, distance / 10));
      if (game.time % frequency == 0)
        grid->plrc->x_pos++;
    }

    // NO INPUT
    if (retv <= 0)
    {
      handle_no_input(game, grid);
      handle_anim(grid->plrc, game);
    }

    // INPUT
    if (retv > 0)
    {
      int inp = getchar();
      is_slow_framing = inp == '>';
      set_input(inp, &game, grid);
      handle_anim(grid->plrc, game);

      if (inp == '>')
        is_slow_framing = 1;
      if (inp == 'm')
        game.view_col = !game.view_col;
      if (inp == DEBUG_VIEW_K)
        is_in_debug_menu = !is_in_debug_menu;
      if (inp == 'p')
      {
        in_pause_menu = !in_pause_menu;
        print_grid_debug(grid, menu_page);
      }
      while (in_pause_menu)
      {
        int inp = getchar();
        if (inp == 'p')
          in_pause_menu = 0;
        else if (inp == 'd')
        {
          if (menu_page < CELL_BUFFER)
            menu_page += 20;
          print_grid_debug(grid, menu_page);
        }
        else if (inp == 'a')
        {
          if (menu_page - 20 >= 0)
            menu_page -= 20;
          print_grid_debug(grid, menu_page);
        }
        usleep(sleep_time);
        continue;
      }
    }

    if (is_slow_framing)
    {
      int inp = -1;
      while (inp == -1 && inp != DEBUG_VIEW_K)
      {
        inp = getchar();
        if (inp == DEBUG_VIEW_K)
        {
          if (!is_in_debug_menu) print_debug_log(*grid, game, sleep_time);
          is_in_debug_menu = !is_in_debug_menu;
        }
        continue;
      }
      if (inp != '>' && inp != DEBUG_VIEW_K)
        is_slow_framing = 0;
      continue;
    }
  }
  return (0);
}

int main()
{
  set_nonblocking_mode(1);
  srand(time(NULL));
  print_start_menu();
  update_game();
  return (1);
}