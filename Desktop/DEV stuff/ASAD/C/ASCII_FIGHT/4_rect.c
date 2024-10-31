#include "header.h"

int	get_width(const char *canv)
{
	int i = -1;
	int	cur_len = 0;
	int max_len = 0;

	while (canv[++i])
	{
		if (canv[i] == '\n')
		{
			max_len = MAX(max_len, cur_len + 1);
			cur_len = -1;
		}
		cur_len++;
	}
	max_len = MAX(max_len, cur_len + 1);
	return (max_len);
}

int get_height(const char *canv)
{
	int i = -1;
	int height = 0;
	while (canv[++i])
		if (canv[i] == '\n')
			height++;
	return (height);
}

char	*get_rect(char *canv, int width, int height, char interior, int exterior)
{
	int	i = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if ((x == 0 && y == 0) || (x == width-1 && y == height-1) || (x == 0 && y == height-1) || (x == width-1 && y == 0))
				canv[i++] = exterior ? '.' : ' ';
			else canv[i++] = x == 0 || x == width - 1 ? exterior ? VER_COL : ' ' : y == 0 || y == height - 1 ? exterior ? HOR_COL : ' ' : interior;

		}
		canv[i++] = '\n';
	}
	canv[i] = '\0';
	return (canv);
}





char *get_triangle(char *canv, int width, int height, char interior, int exterior) {
    (void)exterior;
    int i = 0;
    float ratio = (float)width / (2 * height);

    for (int y = 0; y < height; y++) {
        int half_width = (int)(ratio * y);
        int x_start = (width / 2) - half_width;
        int x_end = (width / 2) + half_width;
		int next_ratio = ((width / 2) + (int)(ratio * (y + 1)));

        for (int x = 0; x < x_end + 1; x++) {
            if (y == height - 1) canv[i++] = HOR_COL;
			else if (x < x_start && x > x_start - (next_ratio - x_end)) canv[i++] = '_';
			else if (y == 0 && x == width / 2) canv[i++] = '^';
			else if (x < x_start) canv[i++] = ' ';
			else if (x == x_start) canv[i++] = '/';
			else if (x == x_end) canv[i++] = '\\';
			else if (x > x_start && x < x_end) canv[i++] = interior;
            else canv[i++] = ' ';
        }
		if (y < height - 1)
			for (int v = 0; v < next_ratio - x_end - 1; v++)
				canv[i++] = '_';
        canv[i++] = '\n';
    }
    canv[i] = '\0';
    return canv;
}

char *get_house(char *canv, int width, int height, char interior, int exterior, HOUSE_TYPES type)
{
	char top[MAX_CONTENT];
	char bottom[MAX_CONTENT];
	char door[MAX_CONTENT];
	(void)type;

	get_triangle(top, width, height / 3, '-', exterior);
	get_rect(bottom, width, height / 2, interior, exterior);
	get_rect(door, PLAYER.width, PLAYER.height, '.', 1);
	print_string(" -------\n|.......|\n|.....0.|\n|.......|\n|.......|\0", bottom, width / 2 - 4, height / 2 - 6);

	char *first_line_end = strchr(bottom, '\n');
	if (first_line_end) memmove(bottom, first_line_end + 1, strlen(first_line_end + 1) + 1);
	strncpy(canv, top, MAX_CONTENT);
	int len = strlen(canv);
	canv[len] = '\0';
	strcat(canv, bottom);
	return (canv);
}

char *get_house_interior(char *canv, int width, int height, char interior, int exterior, HOUSE_TYPES type)
{
	char rooms[5][MAX_CONTENT];
	(void)type;
	int num_rooms = rand_range(1, 5);
	int room_size = 15;

	int start_x = 0;
	int start_y = 0;

	get_rect(canv, width, height, '#', 0);
	for (int i = 0; i < num_rooms; i++)
	{
		int w = MAX(room_size, width / num_rooms + rand_range(2, 4));
		int y = MAX(room_size, height / num_rooms - rand_range(2, 4));
		if (start_x + w > width){
			start_x = 0;
			start_y += y;
		}
		get_rect(rooms[i], w, y, interior, exterior);
		print_string(rooms[i], canv, start_x, start_y);
		start_x += w + 2;
	}
	return (canv);
}