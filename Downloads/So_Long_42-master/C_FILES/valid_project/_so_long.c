/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _so_long.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:37:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2024/11/11 13:11:30 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../HEADERS/header.h"

#define TILE_SIZE 50

void	render(t_mlx_data *mlx_data)
{
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, \
	mlx_data->background_color, 0, 0);
	if (mlx_data->background_img != NULL)
		mlx_put_image_to_window(mlx_data, mlx_data->win, \
		mlx_data->background_img, 0, 0);
	if (mlx_data->images != NULL)
		render_array(mlx_data, mlx_data->images, NULL);
	render_player(mlx_data);
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

t_ent	*get_rand_copy(t_ent **images)
{
	t_ent	*ent;
	int		len;

	if (!images)
		return (NULL);
	len = get_array_size((void **)images);
	ent = copy_ent(images[rand_range(0, len - 1)]);
	return (ent);
}

void handle_entity_frames(t_mlx_data *mlx_data, t_ent *e, void *path, t_vec2 scale)
{
	char	**frames;
	int		frames_amount;

	frames_amount = e->frames_amount;
	frames = get_frames_paths(path, "", frames_amount);
	e->anim_frames = malloc(sizeof(void *) * (frames_amount + 1));
	if (!e->anim_frames)
	{
		free(e);
		return ;
	}
	e->frames_amount = -1;
	while (frames[++e->frames_amount] && e->frames_amount < frames_amount)
	{
		e->anim_frames[e->frames_amount] = add_img(frames[e->frames_amount], \
			&e->size.x, &e->size.y, mlx_data);
		if (!e->anim_frames[e->frames_amount])
			break ;
		e->anim_frames[e->frames_amount] = rescale_image(mlx_data, \
			e->anim_frames[e->frames_amount], &e->size, scale);
	}
	printf("%d FRAMES successfully turned into an image [%s]\n", \
		e->frames_amount, frames[e->frames_amount - 1]);
	e->anim_frames[e->frames_amount] = NULL;
	e->cur_frame = e->anim_frames[rand_range(0, e->frames_amount - 1)];
	free(frames);
}

// VALUES.x > scale, VALUE.y > type, VALUE.z > frames_amount
t_ent	*init_entity(t_mlx_data *mlx_data, void *path, t_vec3 pos, \
	t_vec3 values)
{
	t_ent	*e;

	e = malloc(sizeof(t_ent));
	if (!e)
		return (NULL);
	e->pos = get_Vec3(pos.x * TILE_SIZE, pos.y * TILE_SIZE, 0);
	set_Vec2(&e->follow_ofs, rand_range(-10, 10), rand_range(-5, 5));
	set_Vec3(&e->movement, 0, 0, 0);
	e->is_grounded = 1;
	e->flip_x = 0;
	e->jumps = 2;
	e->hp = 1;
	e->cur_frame_index = 0;
	e->frames_amount = values.z;
	e->jet_sky_timer = 0;
	e->base_pos = e->pos;
	e->type = values.y;
	handle_entity_frames(mlx_data, e, path, get_Vec2(values.x, values.x));
	return (e);
}

int	init_player(t_mlx_data *mlx_data, char *path, t_vec3 pos)
{
	char	**idle_frames;
	char	**wlk_frm;
	t_ent	*player;

	player = &mlx_data->player;
	player->is_grounded = 1;
	player->flip_x = 0;
	player->jumps = 2;
	player->jet_sky_timer = 0;
	player->pos = get_Vec3(pos.x * TILE_SIZE, pos.y * TILE_SIZE, 0);
	set_Vec3(&player->movement, 0, 0, 0);
	set_Vec2(&player->size, 50, 50);
	player->type = Player;
	idle_frames = get_frames_paths(path, "IDLE_", 2);
	wlk_frm = get_frames_paths(path, "WALK_", 2);
	player->walk_frame_amount = 2;
	player->idle_frame_amount = 2;
	set_entity_frames(mlx_data, &mlx_data->player, wlk_frm, idle_frames);
	return (1);
}

t_ent *parse_letter(t_mlx_data *mlx_data, t_vec3 pos, char c)
{
	int	scale;
	t_ent *ent;

	ent = NULL;
	scale = TILE_SIZE;
	if (c == '1')
		ent = init_entity(mlx_data, WALL_SPRITES_PATH, pos, get_Vec3(scale, wall, 2));
	else if (c == 'C')
		ent = init_entity(mlx_data, COLLECTIBLES_SPRITES_PATH, pos, \
			get_Vec3(TILE_SIZE - rand_range(35, 40), coin, 13));
	else if (c == 'T')
		ent = init_entity(mlx_data, TILES_SPRITES_PATH, pos, \
			get_Vec3(scale / 2, tile, 11));
	else if (c == 'E')
		ent = init_entity(mlx_data, PORTAL_SPRITES_PATH, \
			pos, get_Vec3(scale, exitance, 9));
	else if (c == 'M')
		ent = init_entity(mlx_data, "RESSOURCES/PNG/ENTITIES/MOBS/IDLE_", \
			pos, get_Vec3(scale, mob, 2));
	else if (c == 'P')
		init_player(mlx_data, PLAYER_SPRITES_PATH, pos);
	
	
	return (ent);
}

int get_ents_from_map(t_mlx_data *mlx_data, char *file_path, int amount)
{
	t_ent	*e;
	t_vec3	pos;
	char	*line;
	int		fd;

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
			break ;
		free(line);
		line = get_next_line(fd);
	}
	mlx_data->images[mlx_data->images_len] = NULL;
	close(fd);
	return (mlx_data->images_len);
}

t_vec2	get_map_dimensions(int fd)
{
	int		width;
	char	*line;
	t_vec2	res;

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

t_vec2	load_valid_map(char *file_path)
{
	int		fd;
	t_vec2	size;

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
	t_vec2		size;
	t_mlx_data	mlx_data;
	t_vec2		background_size;
	int			width;
	int			height;

	set_Vec2(&size, 5, 5);
	mlx_data.time = 0;
	srand(time(0));
	mlx_data.images_len = 0;
	init_mlx(&mlx_data);
	if (argc == 2)
		size = load_valid_map(argv[1]);
	printf("SIZE LOADED: %d %d", size.x, size.y);
	mlx_data.win = mlx_new_window(mlx_data.mlx, size.x * TILE_SIZE, \
	(size.y + 1) * TILE_SIZE, "g");
	mlx_data.background_color = mlx_new_image(mlx_data.mlx, size.x * \
	TILE_SIZE, size.y * TILE_SIZE);

	mlx_data.background_img = mlx_png_file_to_image(&mlx_data, \
	"RESSOURCES/PNG/BACKGROUND/5.png", &width, &height);
	mlx_data.background_img = rescale_image(&mlx_data, mlx_data.background_img, \
	&background_size, get_Vec2(size.x * TILE_SIZE, (size.y + 1) * TILE_SIZE));
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
