#include "_ascii.h"
#include "_header.h"

void set_nonblocking_mode(int enable)
{
  static struct termios oldt, newt;
  if (enable)
  {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
  }
  else
  {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, 0);
  }
}

char *get_rect(int width, int height, char interior, char interior2, char brd_left,
               char brd_right, char brd_up, char brd_down)
{
  int init_height = height;
  int rand_height = 0;
  int has_liane = -1;

  if (interior2 == GR_TOP_IC && rand() % LIANE_CHANCE == 0)
  {
    rand_height = rand_range(3, 20);
    height += rand_height;
    has_liane = rand_range(1, width - 1);
  }

  char *buff = malloc((width + 1) * height + 1);
  int i = 0;
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      char c = ' ';
      if (has_liane && y >= init_height)
      {
        if (x == has_liane)
          c = y == height - 1 ? LIANE_END_ic : y == init_height ? LIANE_START
                                           : y % 2 == 0         ? LIANE1
                                                                : LIANE2;
        else
          c = ' ';
      }

      else if (y == 0 && x > 0 && x < width - 1)
        c = brd_up;
      else if (y == height - rand_height - 1 && x > 0 && x < width - 1)
        c = brd_down;
      else if (x == 0 && y > 0 && y < height - rand_height - 1)
        c = brd_left;
      else if (x == width - 1 && y > 0 && y < height - rand_height - 1)
        c = brd_right;
      else if ((x == 0 && y == 0) || (x == 0 && y == height - rand_height - 1) ||
               (x == width - 1 && y == 0) ||
               (x == width - 1 && y == height - rand_height - 1))
        c = '.';
      else
        c = y < 2 && interior2 != ' ' && interior2 != '\0' ? interior2 : interior;
      buff[i++] = c;
    }
    buff[i++] = '\n';
  }
  if (has_liane) buff[0] = '#';
  buff[i] = '\0';
  return buff;
}

int get_width(char *buff)
{
  int i = 0;
  int max_x = 0;
  int cur_x = 0;
  while (buff[i])
  {
    if (buff[i] == '\n')
    {
      if (max_x < cur_x)
        max_x = cur_x;
      cur_x = 0;
    }
    cur_x++;
    i++;
  }
  return (max_x - 1);
}

int get_height(char *buff)
{
  int i = 0;
  int y = 0;
  while (buff[i])
  {
    if (buff[i] == '\n')
      y++;
    i++;
  }
  return (y);
}

int rand_range(int min, int max)
{
  if (min > max)
    return max;
  return min + rand() % (max - min + 1);
}

int is_in_string(char c, char *sep)
{
  int i = 0;
  while (sep[i])
    if (sep[i++] == c) return (1);
  return (0);
}

void noisify(char *dst, int noise_chance, int neigh_chance, char *avoid)
{
  int i = 0;
  if (noise_chance == 0) return;
  while (dst[i])
  {
    if (rand_range(0, noise_chance) == 0)
    {
      if ((avoid == NULL || !is_in_string(dst[i], avoid)) && dst[i] != '\n' && (dst[i] > 33 && dst[i] < 50))
      {
        dst[i] = rand_range(33, 50);

        if (neigh_chance && rand_range(0, neigh_chance) == 0)
        {
          int r = rand() % 4;
          int ind = r == 0 ? i - 1 : r == 1 ? i + 1
                                 : r == 2   ? i - WIN_X_MAX - 1
                                            : i + WIN_X_MAX + 1;
          if (dst[ind] && dst[ind] != '\n')
            dst[ind] = rand_range(33, 50);
        }
      }
    }
    i++;
  }
}

int is_duplicate(cell_type type, int x_pos, int y_pos, Grid grid)
{
  int i = 0;
  while (grid.cells[i].text)
  {
    if (grid.cells[i].c_type == type)
    {
      if (grid.cells[i].x_pos == x_pos && grid.cells[i].y_pos == y_pos)
        return (1);
    }
    i++;
  }
  return (0);
}

int print_on_grid(char *src, char *dst, int x_pos, int y_pos, int loop)
{
  if (!src || !dst)
  {
    perror("(Add to grid): src or dst was null");
    return 0;
  }

  (void)loop;
  int res = 1;

  int x_size = get_width(dst);
  int src_width = get_width(src);
  int src_height = get_height(src);

  char *tmp = malloc(strlen(dst) + 1);
  if (!tmp)
  {
    perror("Memory allocation failed");
    return 0;
  }
  strcpy(tmp, dst);

  int start_ind = x_pos + ((x_size + 1) * (y_pos));
  int u = 0;

  for (int y = 0; y <= src_height; y++)
  {
    if (start_ind >= strlen(tmp) || !src[u])
      break;

    for (int x = 0; x < src_width; x++)
    {
      if (src[u] == '\0' || src[u] == '\n' || start_ind + x >= strlen(tmp))
        break;

      if (src[u] != ' ' && tmp[start_ind + x] != '\n')
        tmp[start_ind + x] = src[u];

      u++;
    }

    if (src[u] == '\0')
      break;

    u++;
    start_ind += x_size + 1;

    // Ensure start_ind is within bounds
    if (start_ind >= strlen(tmp))
    {
      res = 0;
      break;
    }
  }

  strcpy(dst, tmp);
  free(tmp);
  return res;
}

int erase(char *dst, int x_pos, int y_pos, int x_len, int y_len, char *dont_erase)
{
  if (!dst) return 0;
  int x_size = get_width(dst);

  char *tmp = malloc(strlen(dst) + 1); // +1 for null terminator
  if (!tmp) return 0;
  strcpy(tmp, dst);

  unsigned int start_ind = x_pos + (x_size + 1) * y_pos;

  for (int y = 0; y < y_len; y++)
  {
    if (start_ind >= strlen(tmp))
      break;

    for (int x = 0; x < x_len; x++)
    {
      if (start_ind + x >= strlen(tmp))
        break;

      if (tmp[start_ind + x] != '\n')
      {
        if (!dont_erase || !is_in_string(tmp[start_ind + x], dont_erase))
          tmp[start_ind + x] = ' ';
      }
    }

    start_ind += x_size + 1;
  }

  strcpy(dst, tmp);
  free(tmp);
  return 1;
}

int get_win_x()
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return (w.ws_col);
}

int get_win_y()
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return (w.ws_row);
}