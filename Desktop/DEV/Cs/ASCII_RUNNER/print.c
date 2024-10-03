#include "_ascii.h"
#include "_header.h"

int print_start_menu()
{
  system("clear");

  int time = 0;
  int go_back = 0;
  int can_start = 0;

  char *tree = strdup(tree1);
  char *tit = strdup(title);
  char *c_text = NULL;

  printf("\n\n\n\n");
  mini_cell c;
  char *noise_terrain = get_rect(30, 20, '*', ' ', '|', '|', '|', '|');
  int i = 0;
  while (noise_terrain[i])
  {
    if (noise_terrain[i] != '\n')
      noise_terrain[i++] = rand() % 500 == 0 ? '.' : ' ';
    i++;
  }
  noise_terrain[i] = '\0';

  while (!can_start)
  {
    int inp = getchar();
    if (inp != -1) can_start = 1;
    usleep(REF_SPEED * 1000000);
    system("clear");
    time++;

    if (time % 500 == 0) go_back = !go_back;

    int win_x = get_win_x();
    char *tit_canv = get_rect(win_x, 30, ' ', ' ', ' ', ' ', ' ', ' ');
    char *empty_tit_canv = get_rect(win_x, 30, ' ', ' ', ' ', ' ', ' ', ' ');
    int canv_len = strlen(tit_canv);
    print_on_grid(tit, tit_canv, get_width(tit_canv) / 2 - get_width(tit) / 2, get_height(tit_canv) / 2 - get_height(tit) / 2, 0);
    c.start_text = tit_canv;

    if (time == 1)
      c_text = strdup(c.start_text);
    else if (c_text == NULL)
      c_text = strdup(c.start_text);

    i = 0;
    while (c_text[i] && c.start_text[i])
    {
      int r = rand() % 50;
      if (c_text[i] != '\n')
      {
        if (c.start_text[i] == '#') c.start_text[i] = ' ';

        if (go_back && r == 0)
          c_text[i] = c.start_text[i];
        else if (r == 0)
        {
          if (c.start_text[i] == ' ' || (c.start_text[i] >= 'A' && c.start_text[i] <= 'Z'))
          {
            // PROBLEM: GOTTA CHECK THAT I is more than 0 and less than max index

            // if ((c.start_text[i] >= 'A' && c.start_text[i] <= 'Z') || (is_in_string(c.start_text[i + 1], "ASCIRUN:") || is_in_string(c.start_text[i - 1], "ASCIRUN:") || is_in_string(c.start_text[i + win_x + 1], "ASCIRUN:") || is_in_string(c.start_text[i - win_x - 1], "ASCIRUN:")))
            //   c_text[i] = rand_range(33, 126);
            // else if (rand() % 400 == 0)
            //  c_text[i] = '.';
          }
          else
            c_text[i] = ' ';
        }
      }
      printf("%c", c_text[i++]);
    }
    i = 0;
    free(tit_canv);
    free(empty_tit_canv);

    printf("\n\n");

    fit_to_window(noise_terrain);

    int i = 0;
    while (noise_terrain[i])
      printf("%c", noise_terrain[i++]);
  }

  // Free the allocated memory
  free(noise_terrain);
  free(tit);
  free(tree);
  free(c_text);

  return (0);
}

int print_end_menu(Grid grid, Game game)
{
  (void)grid;
  (void)game;

  int inp = -1;
  system("clear");
  printf("YOU LOST\n");
  printf("REstart = ANY KEY\n");
  printf("q - QUIT");

  while (inp == -1)
  {
    inp = getchar();
    if (inp == 'q')
      return (0);
    else if (inp == 'r')
      return (1);
  }
  return (1);
}

void crop_text(char *txt, int x_crop, int y_crop, char background)
{
  if (y_crop == 0 && x_crop == 0) return;

  int i = 0;
  int x = 0;
  int y = 0;

  int y_size = get_height(txt) - 1;
  int x_size = get_width(txt) - 1;

  while (txt[i])
  {
    if (x < x_crop || (txt[i] != '\n' && txt[i] != '\0' && x >= x_size - x_crop))
      txt[i] = background;

    if (y < y_crop || y > y_size - y_crop)
    {
      if (txt[i] != '\n')
        txt[i] = background;
    }

    if (txt[i] == '\n')
    {
      x = -1;
      y++;
    }

    x++;
    i++;
  }
}

char *fit_to_window(char *text)
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int win_x = w.ws_col;
  int win_y = w.ws_row;

  char *cropped = malloc(win_x * win_y + win_y + 1);

  int txt_index = 0;
  int i = 0;
  for (int y = 0; y < win_y; y++)
  {
    for (int x = 0; x < win_x; x++)
    {
      if (text[txt_index] == '\0') break;
      cropped[i++] = text[txt_index++];
    }
    cropped[i++] = '\n';

    while (text[txt_index] != '\0' && text[txt_index] != '\n')
      txt_index++;
    if (text[txt_index] == '\n')
      txt_index++;
  }
  cropped[i] = '\0';
  return (cropped);
}

void print_grid(Grid grid, Game game, int x_crop, int y_crop, char background)
{
  system("clear");
  grid.txt = fit_to_window(grid.txt);
  // crop_text(grid.txt, x_crop, y_crop, background);
  int map_size = strlen(grid.txt);
  int i = 0;
  while (grid.txt[i])
  {
    if (i < map_size && grid.txt[i + 1] == '\n')
    {
      printf("n");
    }
    else if (grid.txt[i] == VER_IGN_IC)
      printf("|");
    else if (grid.txt[i] == GR_INT_IC)
    {
      // printf(" ");
      // print_unicode_block(BROWN, WHITE_SQUARE);
      print_colored_text(NULL, 'O', BROWN);
    }
    else if (grid.txt[i] == GR_TOP_IC)
    {
      print_colored_text(NULL, 'O', GREEN);
      // print_colored_text(NULL, '*', GREEN);
      // print_unicode_block(GREEN, WHITE_SQUARE);
    }
    else if (grid.txt[i] == GRASS_IC)
      print_colored_text(NULL, '/', GREEN);
    else if (grid.txt[i] == STAR_IC)
      print_colored_text(NULL, '.', rand() % 2 == 0 ? PALE_YELLOW : DIM_WHITE);
    else if (grid.txt[i] == RAIN_IC)
      print_colored_text(NULL, '|', rand() % 2 == 0 ? BLUE : LIGHT_BLUE);
    else if (grid.txt[i] == RAINSPL_IC)
      print_colored_text(NULL, ',', rand() % 2 == 0 ? BLUE : LIGHT_BLUE);
    else if (grid.txt[i] == LIANE_START)
      print_colored_text(NULL, 'V', DARK_GREEN);
    else if (grid.txt[i] == LIANE1)
      print_colored_text(NULL, rand() % 2 == 0 ? '(' : ']', DARK_GREEN);
    else if (grid.txt[i] == LIANE2)
      print_colored_text(NULL, rand() % 2 == 0 ? '(' : ']', GREEN);
    else if (grid.txt[i] == LIANE_END_ic)
      print_colored_text(NULL, '#', DARK_GREEN);
    else if (grid.txt[i] == RAND_IC)
      print_colored_text(NULL, rand_range(33, 126), MAGENTA);
    else if (grid.txt[i] == 'T' || grid.txt[i] == 'c')
    {
      if (game.view_col)
        print_unicode_block(grid.txt[i] == '#' ? BLUE : grid.txt[i] == 'T' ? RED
                                                                           : GREEN,
                            FULL_BLOCK);
      else
        printf(" ");
    }
    else if (grid.txt[i] == '#')
      printf(" ");
    else
      printf("%c", grid.txt[i]);

    i++;
  }
}

void print_unicode_block(char *color, char *block_char)
{
  if (color != NULL)
    printf("%s%s\033[0m", color, block_char);
  else
    printf("%s", block_char);
}

void print_colored_text(char *c, char cc, char *color)
{
  if (color != NULL)
  {
    if (c != NULL)
    {
      int i = 0;
      while (c[i])
        printf("%s%c\033[0m", color, c[i++]);
    }
    if (cc != '\0')
      printf("%s%c\033[0m", color, cc);
  }
  else
  {
    // Print without color
    if (c != NULL)
      printf("%s", c);
    if (cc != '\0')
      printf("%c", cc);
  }
}