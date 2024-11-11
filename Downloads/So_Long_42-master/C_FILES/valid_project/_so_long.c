/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _so_long.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:37:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/11 06:41:37 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

#define tile_size 50


void	render(t_mlx_data *mlx_data)
{
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
	mlx_data->background_color, 0, 0);
	if (mlx_data->background_img != NULL)
		mlx_put_image_to_window(mlx_data, mlx_data->win, mlx_data->background_img, 0, 0);
	render_player(mlx_data);
	if (mlx_data->images != NULL)
		render_array(mlx_data, mlx_data->images, NULL);
}

int	update_and_render(t_mlx_data *mlx_data)
{
	update_mouse(mlx_data);
	update(mlx_data);
	render(mlx_data);
	reset_mlx_values(mlx_data);
	mlx_data->time++;
	return (0);
}

t_ent *get_rand_copy(t_ent **images)
{
	t_ent *ent;
	int len;

	if (!images)
		return (NULL);
	len = get_array_size((void**)images);
	ent = copy_ent(images[rand_range(0, len - 1)]);
	return (ent);
}
t_ent *init_entity(t_mlx_data *mlx_data, void *frames_path, t_Vec3 pos, t_Vec2 scale, t_ent_type type, int frames_amount)
{
    char **frames;
    int frame_index;
    t_ent *e;

    e = malloc(sizeof(t_ent));
    if (!e)
        return NULL;
    e->is_grounded = 1;
    e->flip_x = 0;
    e->jumps = 2;
	set_Vec2(&e->follow_ofs, rand_range(-10, 10), rand_range(-5, 5));
	e->hp = 1;
    e->jet_sky_timer = 0;
    e->pos = get_Vec3(pos.x * tile_size, pos.y * tile_size, 0);
    e->base_pos = e->pos;
    set_Vec3(&e->movement, 0, 0, 0);
    e->type = type;
    frames = get_frames_paths(frames_path, "", frames_amount);
    e->anim_frames = malloc(sizeof(void *) * (frames_amount + 1));
    if (!e->anim_frames) {
        free(e);
        return NULL;
    }

    frame_index = -1;
    while (frames[++frame_index]) 
	{
        e->anim_frames[frame_index] = add_img(frames[frame_index], &e->size.x, &e->size.y, mlx_data);
		e->anim_frames[frame_index] = rescale_image(mlx_data, e->anim_frames[frame_index], &e->size.x, &e->size.y, scale.x, scale.y);
    }
	printf("%d FRAMES successfully turned into an image [%s]\n", frame_index, frames[frame_index- 1]);
    e->anim_frames[frame_index] = NULL;
    e->cur_frame = e->anim_frames[rand_range(0, frames_amount - 1)];
    free(frames);
    return e;
}

int	init_player(t_mlx_data *mlx_data, char *frames_path, t_Vec3 pos)
{
	char	**idle_frames;
	char	**wlk_frm;
	t_ent	*player;

	player = &mlx_data->player;
	player->is_grounded = 1;
	player->flip_x = 0;
	player->jumps = 2;
	player->jet_sky_timer = 0;
    player->pos = get_Vec3(pos.x * tile_size, pos.y * tile_size, 0);
	set_Vec3(&player->movement, 0, 0, 0);
	set_Vec2(&player->size, 50, 50);
	player->type = Player;
	idle_frames = get_frames_paths(frames_path, "IDLE_", 2);
	wlk_frm = get_frames_paths(frames_path, "WALK_", 2);
	player->walk_frame_amount = 2;
	player->idle_frame_amount = 2;
	set_entity_frames(mlx_data, &mlx_data->player, wlk_frm, idle_frames);
	return (1);
}


t_ent *parse_letter(t_mlx_data *mlx_data, t_Vec3 pos, char c)
{
	t_Vec2 scale;
	
	set_Vec2(&scale, tile_size, tile_size);
	if (c == '1')
		return (init_entity(mlx_data, WALL_SPRITES_PATH, pos, scale, wall, 2));
	else if (c == 'C')
		return (init_entity(mlx_data, COLLECTIBLES_SPRITES_PATH, pos, get_Vec2(tile_size - rand_range(35, 40), tile_size - rand_range(35, 40)), coin, 13));
	else if (c == 'T')
		return (init_entity(mlx_data, TILES_SPRITES_PATH, pos, get_Vec2(scale.x / 2, scale.y / 2), tile, 11));
	else if (c == 'E')
		return (init_entity(mlx_data, TREES_SPRITES_PATH, pos, scale, exitance, 2));
	else if (c == 'M')
		return (init_entity(mlx_data, "RESSOURCES/PNG/ENTITIES/MOBS/IDLE_", pos, scale, mob, 2));
	else if (c == 'P')
		init_player(mlx_data, PLAYER_SPRITES_PATH, pos);
	return (NULL);
}

int get_ents_from_map(t_mlx_data *mlx_data, char *file_path, int amount)
{
	t_ent *e;
	t_Vec3 pos;
	char *line;
	int fd;

	mlx_data->images = malloc(sizeof(t_ent *) * (amount + 1));
	if (!mlx_data->images)
		return (0);
	set_Vec3(&pos, -1, -1, 0);
	fd = open(file_path, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		pos.y++;
		pos.x = -1;
		while (line[++pos.x] && mlx_data->images_len < amount - 1)
		{
			e = parse_letter(mlx_data, pos, line[pos.x]);
			if (e != NULL)
				mlx_data->images[mlx_data->images_len++] = e;
		}
		if (mlx_data->images_len >= amount -1)
			break;
		free(line);
		line = get_next_line(fd);
	}
	mlx_data->images[mlx_data->images_len] = NULL;
	close(fd);
	return (mlx_data->images_len);
}


t_Vec2 get_map_dimensions(int fd)
{
    int width;
    char *line;
    t_Vec2 res;

    set_Vec2(&res, -1, -1);
    line = get_next_line(fd);
    res.x = ft_strlen(line);
    if (line[res.x - 1] == '\n')
        res.x--;
    while (line != NULL)
    {
        res.y++;
        width = ft_strlen(line);
        if (line[width - 1] == '\n')
            width--;
        if (width != res.x)
        {
            set_Vec2(&res, -1, -1);
            free(line);
            return (res);
        }
        free(line);
        line = get_next_line(fd);
    }
    return (res);
}

t_Vec2 load_valid_map(char *file_path)
{
	int fd;
	t_Vec2 size;
	
	set_Vec2(&size, 5,5);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (size);
	size = get_map_dimensions(fd);
	if (size.x <= 0 || size.y <= 0)
	{
		ft_printf("x%d y%d - MAP NOT VALID", size);
		perror("map not valid");
		exit(0);
	}
	return (size);
}

int	init_mlx(t_mlx_data *mlx_data)
{
	int	i;

	i = -1;
	mlx_data->game_mobs = NULL;
	while (++i < 512)
		mlx_data->key_state[i] = 0;
	mlx_data->mlx = mlx_init();
	mlx_data->mouse_button = 0;
	mlx_data->background = NULL;
	mlx_data->images_len = 0;
	return (1);
}


int	main(int argc, char **argv)
{
	t_Vec2 size;
	t_mlx_data	mlx_data;

	set_Vec2(&size, 5,5);
	mlx_data.time = 0;
	srand(time(0));
	//load_images(&mlx_data);
	mlx_data.images_len = 0;
	init_mlx(&mlx_data);
	if (argc == 2)
		size = load_valid_map(argv[1]);
	printf("SIZE LOADED: %d %d", size.x, size.y);

	mlx_data.win = mlx_new_window(mlx_data.mlx, size.x * tile_size, (size.y + 1) * tile_size, "g");
	mlx_data.background_color = mlx_new_image(mlx_data.mlx, size.x * tile_size, size.y * tile_size);
	
	int width;
	int height;
	mlx_data.background_img = mlx_png_file_to_image(&mlx_data, "RESSOURCES/PNG/BACKGROUND/5.png", &width, &height);
	mlx_data.background_img = rescale_image(&mlx_data, mlx_data.background_img, &width, &height, size.x * tile_size, (size.y + 1) * tile_size);
	mlx_data.addr = mlx_get_data_addr(mlx_data.background_color, \
		&mlx_data.bits_per_pixel, &mlx_data.line_length, &mlx_data.endian);
	get_ents_from_map(&mlx_data, argv[1], size.x * size.y);
	mlx_data.game_mobs = NULL;
	init_mouse(&mlx_data);
	mlx_hook(mlx_data.win, KEY_PRESS, 0, handle_key_press, &mlx_data);
	mlx_hook(mlx_data.win, KEY_RELEASE, 0, handle_key_release, &mlx_data);
	mlx_loop_hook(mlx_data.mlx, (int (*)())update_and_render, &mlx_data);
	mlx_loop(mlx_data.mlx);
	return (0);
}
