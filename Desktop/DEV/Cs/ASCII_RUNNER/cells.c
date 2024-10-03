#include "_ascii.h"
#include "_header.h"

const char *CELL_NAMES[] = {"player", "NPC", "mob0", "mob1", "env", "ground", "BKGrnd",
                            "coin", "food", "empty", "null"};

const char *ACTION_NAMES[] = {"idle", "walk", "run", "dash",
                              "jump", "db_jump", "land", "fly",
                              "fall", "spell_cast", "attack"};

const char *DIR_NAMES[] = {"up", "up_left", "up_right",
                           "down", "down_left", "down_right",
                           "left", "right", "none"};

void set_sky(Sky_c *c, char icon, directions dir, int lifetime)
{
  c->index = rand_range(0, WIN_Y_MAX * (WIN_X_MAX + 1));
  c->lifetime = lifetime;
  c->c = icon;
  c->dir = dir;
}

Grid *init_grid()
{
  int i = 0;
  Grid *grid = malloc(sizeof(Grid));
  grid->cells = malloc(sizeof(Cell) * (CELL_BUFFER + 1));
  grid->sky_c = malloc(sizeof(Sky_c) * (SKY_BUFFER + 1));

  for (int x = 0; x < SKY_BUFFER; x++)
    set_sky(&grid->sky_c[x], RAIN_IC, down, rand_range(0, RAIN_DUR + RAIN_DUR / 2));
  grid->sky_c[SKY_BUFFER].c = '\0';

  grid->cells_amnt = CELL_BUFFER + 1;
  while (i < CELL_BUFFER)
    set_cell("EMPTY", empty, empty, &grid->cells[i++], NULL, 0, 0, 0, 0, 0, 0,
             0, 0, 0);
  set_cell("NULL", null, null, &grid->cells[i], NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  return (grid);
}

void set_cell(char *name, cell_type type, cell_type nxt_type, Cell *c,
              char *content, int p_dir, char dir, int tick, int life_tick,
              int width, int height, int x_pos, int y_pos, int scroll_speed)
{
  c->text = content != NULL ? strdup(content) : NULL;
  c->c_type = type;
  c->next_c_type = nxt_type;
  c->name = name;
  c->c_action = idle;
  c->should_loop = 1;
  c->scroll_speed = scroll_speed;
  c->dir = right;
  c->p_dir = p_dir;
  c->dir = dir;
  c->tick = tick;
  c->life_tick = life_tick;
  c->width = width;
  c->height = height;
  c->x_pos = x_pos;
  c->y_pos = y_pos;
  c->start_x = x_pos;
  c->start_y = y_pos;
}

int set_dynamic_cell(char *name, char *content, int x_pos, int y_pos,
                     cell_type type, Grid *grid, int index, int scroll_speed, int shld_loop)
{
  if (name == NULL || content == NULL) return (-1);
  if (index < 0 || grid->cells[index].c_type != empty)
    index = get_free_index(*grid);
  if (index == -1) return (index);

  if (type == ground)
    for (int x = 0; x < (get_width(content) - 1); x++)
      if (rand() % 5 == 0) content[x] = GRASS_IC;
  set_cell(name, type, type, &grid->cells[index], content, 0, 0, 0, 0,
           get_width(content), get_height(content), x_pos, y_pos,
           scroll_speed);
  grid->cells[index].should_loop = shld_loop;
  return (index);
}

void set_empty_cell(Cell *cell)
{
  if (cell->text != NULL)
    free(cell->text);
  set_cell(NULL, null, null, cell, NULL, 0, 0, -1, -1, -1, -1, -1, -1, -1);
}

void erase_cell(Grid *grid, int index)
{
  while (grid->cells[index + 1].text && grid->cells[index + 1].c_type != empty)
  {
    grid->cells[index] = grid->cells[index + 1];
    if (grid->cells[index].c_type == player) grid->plrc = &grid->cells[index];
    index++;
  }
  if (grid->cells[index].c_type == empty)
    set_empty_cell(&grid->cells[index]);
}

int get_free_index(Grid grid)
{
  int i = 0;
  while (i < grid.cells_amnt && grid.cells[i].c_type != empty)
    i++;
  if (i >= grid.cells_amnt)
    return -1;
  return i;
}

int init_mob(char *name, Grid *grid, int x_pos, int y_pos, int index, int scroll_speed)
{
  if (index < 0 || grid->cells[index].c_type != empty)
    index = get_free_index(*grid);
  if (index == -1)
    return (index);
  set_cell(name, mob0, mob0, &grid->cells[index], mob_1_left1, rand() % 2,
           rand() % 2, 0, 0, get_width(mob_1_left1), get_height(mob_1_left1),
           x_pos, y_pos, scroll_speed);
  return (index);
}
int init_plrc(char *name, Grid *grid, int index)
{
  if (index < 0 || grid->cells[index].c_type != empty)
    index = get_free_index(*grid);
  if (index == -1)
    return (index);
  set_cell(name, player, player, &grid->cells[index], plr_mv_right1, 0, 0, 0,
           0, get_width(plr_idle_down1), get_height(plr_idle_down1),
           PLR_START_X, PLR_START_Y, 0);
  Cell *c = &grid->cells[index];
  grid->plrc = c;

  return (index);
}
Cell get_empty_cell()
{
  Cell empty;
  empty.text = NULL;
  empty.name = NULL;
  empty.c_type = null;
  empty.c_action = idle;
  empty.next_c_type = null;
  return (empty);
}

int is_cell_at_index(Cell cell, int x_pos, int y_pos)
{
  if (cell.text == NULL || cell.c_type == empty)
    return (0);
  if ((cell.x_pos >= x_pos && cell.y_pos >= y_pos))
    return (1);
  return (0);
}

int add_to_grid(Cell cell, char *map)
{
  // if (!cell.should_loop)
  {
    int map_Xs = get_width(map);
    int map_Ys = get_height(map);
    if (cell.x_pos >= map_Xs || cell.y_pos >= map_Ys)
      return (0);
    if (cell.x_pos + cell.width <= 0 || cell.y_pos + cell.height <= 0)
      return (0);
  }

  return (print_on_grid(cell.text, map, cell.x_pos, cell.y_pos, cell.should_loop));
}
