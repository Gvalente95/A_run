/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_parsefile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:16:29 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/10 21:23:04 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

int save_to_file(t_mlx_data *mlx_data, int len)
{
	t_ent *ent;
	int i;
	FILE *file = fopen("new_map.ber", "w");
	
	if (mlx_data->background)
		fprintf(file, "bx%d y%d w%d y%d t%d p%s\n", 0, 0, mlx_data->background->size.x, mlx_data->background->size.y, background, mlx_data->background->frame_path);
	i = -1;
	while (++i < len)
	{
		ent = mlx_data->images[i];
		if (ent)
		{
			fprintf(file, "x%d y%d w%d y%d t%d p%s\n", ent->pos.x, ent->pos.y, ent->size.x, ent->size.y, ent->type, ent->frame_path);
			printf("NEW ENT SAVED | PATH %s | TYPE %d | POS[%d,%d] SIZE[%d,%d]\n", ent->frame_path, ent->type, ent->pos.x, ent->pos.y, ent->size.x, ent->size.y);
		}
	}
	fclose(file);
	return (0);
}

char *find_next_occurrence(const char *str, int start_index)
{
	char *substring;
	int len = 0;

	while (str[start_index + len] && str[start_index + len] >= '0' && str[start_index + len] <= '9')
		len++;
    substring = (char *)malloc(len + 1);
    if (!substring)
        return NULL;

	for (int i = 0; i < len; i++)
		substring[i] = str[start_index + i];
    substring[len] = '\0';
    return substring;
}

int get_value(char *line, int *start_index)
{
	char *substring;
	int res = -1;

	(*start_index)++;
	substring = find_next_occurrence(line, *start_index);
	if (substring)
	{
		res = atoi(substring);
		*start_index += strlen(substring);
		free(substring);
	}
	return res;
}

t_ent *parse_line(char *line)
{
	t_ent *ent; 
	int i = 0;
	int i_path = 0;
	char path[500] = {0};
	int values[5] = {0};
	int val_index = 0;
	ent = malloc(sizeof(t_ent));
	if (!ent)
		return NULL;


	while (line[i] && line[i] != '\n')
	{
		if ((line[i] == 'x' || line[i] == 'y' || line[i] == 'w' || line[i] == 'h' || line[i] == 't') && val_index < 5)
			values[val_index++] = get_value(line, &i);
		else if (line[i] == 'p')
		{
			i_path = 0;
			while (line[++i] && line[i] != '\n' && i_path < 499)
				path[i_path++] = line[i];
			path[i_path] = '\0';
		}
		i++;
	}
	if (val_index < 5)
	{
		free(ent);
		return NULL;
	}
	ent->pos.x = values[0];
	ent->pos.y = values[1];
	ent->size.x = values[2];
	ent->size.y = values[3];
	ent->type = values[4];
	if (path[0] != '\0')
		ent->frame_path = strdup(path);
	else
		ent->frame_path = NULL;
	return ent;
}

int load_from_file(t_mlx_data *mlx_data, char *file_path)
{
	int width;
	int height;
	int len = 0;
    char *line;
	int fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		t_ent *e = parse_line(line);
		if (e != NULL)
		{
			printf("%s %d %d %d\n", e->frame_path, e->pos.x, e->size.x, e->type);
			e->cur_frame = add_img(e->frame_path, &width, &height, mlx_data);
			if (e->size.x != width || e->size.y != height)
				e->cur_frame = rescale_image(mlx_data, e->cur_frame, &width, &height, e->size.x, e->size.y);
			if (line[0] == 'b')
				mlx_data->background = copy_ent(e);
			else
				mlx_data->images[mlx_data->images_len++] = copy_ent(e);
			free(e);
		}
		free(line);
		line = get_next_line(fd);
	}
    close(fd);
    return len;
}
