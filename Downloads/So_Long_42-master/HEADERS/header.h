/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:32:42 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/09 02:14:46 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <mlx.h>
# include "../RESSOURCES/libft/libft.h"
# include "Keys.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <time.h>
# include "colors.h"

# define BACKGROUND_SPRITE_PATH "RESSOURCES/PNG/BACKGROUND_0.png"

# define WALL_SPRITES_PATH "RESSOURCES/PNG/ENV/WALL/"
# define GROUND_SPRITES_PATH "RESSOURCES/PNG/ENV/GROUND_0.png"

# define PLAYER_SPRITES_PATH "RESSOURCES/PNG/ENTITIES/PLAYER/"
# define MOB_SPRITES_PATH "RESSOURCES/PNG/ENTITIES/MOBS/"

# define PLAYER_IDLE_0 "RESSOURCES/PNG/ENTITIES/PLAYER/IDLE_0.png"
# define PLAYER_IDLE_1 "RESSOURCES/PNG/ENTITIES/PLAYER/IDLE_1"
# define PLAYER_WALK_0 "RESSOURCES/PNG/ENTITIES/PLAYER/WALK_0"
# define PLAYER_WALK_1 "RESSOURCES/PNG/ENTITIES/PLAYER/WALK_1"

# define GROUND_0 "RESSOURCES/PNG/TILES/GROUND_0"
# define WALL_0 "RESSOURCES/PNG/TILES/WALL_0"
# define TEST_IMG "ROADSTOPS.png"

# define RESIZE 1.5
# define WIN_W 	1980
# define WIN_H 	1080

# define MOB_AMOUNT 	10
# define COIN_AMOUNT 10
# define ENV_AMOUNT 50

# define GROUND_LEVEL 880

# define MV_DUR 20
# define MV_AM 2

# define PLAYER_SPEED 2
# define MOBS_SPD 2

# define ANIM_REFRESH 5

typedef enum e_dir
{
	up,
	left,
	down,
	right,
	none,
	DIR_LEN
}	t_dir;

typedef enum e_entity_types
{
	Player,
	mob,
	coin,
	env,
	ENT_TYPE_LEN
}	t_ent_type;

typedef enum e_entity_action
{
	WALK,
	FALL,
	IDLE,
	JUMP,
	ENT_ACTION_LEN
}	t_ent_action;

typedef struct s_Vector2
{
	int	x;
	int	y;
}	t_Vec2;

typedef struct s_Vector3
{
	int	x;
	int	y;
	int	z;
}	t_Vec3;

typedef struct s_entity
{
	void			*cur_frame;
	void			*cur_frame_x;
	void			*wlk_frm[3];
	void			*idl_frm[3];
	void			*wlk_frm_x[3];
	void			*idl_frm_x[3];
	int				walk_frame_amount;
	int				idle_frame_amount;
	int				hp;
	int				is_grounded;
	int				jumps;
	int				flip_x;
	int				jump_timer;
	int				jet_sky_timer;
	int				cur_frame_index;
	t_ent_type		type;
	t_ent_action	action;
	t_dir			dir;
	t_Vec3			pos;
	t_Vec2			size;
	t_Vec3			movement;
}	t_ent;

typedef struct s_mlx_data
{
	t_Vec3		size;
	t_ent		**game_entities;
	t_ent		env[ENV_AMOUNT];
	t_ent		game_coins[COIN_AMOUNT];
	t_ent		game_mobs[MOB_AMOUNT];
	t_ent		player;
	int			key_state[512];
	int			last_key_pressed;
	void		*mlx;
	void		*win;
	void		*background_color;
	void		*background_img;
	void		*ground;
	void		*images;
	void		*tiles;
	char		*addr;
	int			mouse_button;
	int			mouse_pos[2];
	int			god_mode;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			time;
}				t_mlx_data;

// INIT
int		init_mlx_data(t_mlx_data *mlx_data);
int		init_game_entities(t_mlx_data *mlx_data);
// UPDATE
int		update(t_mlx_data *mlx_data);
// RENDER
void	render_images(t_mlx_data *mlx_data);
// IMAGE
void	*add_img(char *relative_path, int *width, int *height, void *mlx);
void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
int		set_entity_frames(t_mlx_data *d, t_ent *e, char **WLK_P, char **IDLE_P);
void	set_img_color(t_Vec2 size, void *frame, int new_color, float intensity);
void	copy_image_data(void *mlx, void *src, void *dest, t_Vec2 size);
void 	*rescale_image(void *mlx, void *img, int *original_width, int *original_height, int new_width, int new_height);

// INPUT
int		handle_key_release(int keycode, t_mlx_data *mlx_data);
int		handle_key_press(int keycode, t_mlx_data *mlx_data);
// TOOLS
void	sort_game_entities_by_z_pos(t_ent *game_entities, int count);
char	**get_frames_paths(char *path, char *suffix, int amount);
int		set_Vec2(t_Vec2 *Vec2, int x, int y);
int		set_Vec3(t_Vec3 *Vec3, int x, int y, int z);
char	print_Vec3(t_Vec3 Vec3);
int		rand_range(int min, int max);
t_Vec3	rand_Vec3(int min, int max);
t_Vec2 	get_Vec2(int x, int y);
t_Vec3 	get_Vec3(int x, int y, int z);
void	*flip_image_x(void *mlx, void *img, int width, int height);

//STUFF
int		get_trgb(unsigned char t, unsigned char r, unsigned char g, \
		unsigned char b);
void	set_brightness(int width, int height, void *frame, float factor);

// COLLISIONS
t_Vec2 	get_collision_displacement(t_ent *entity1, t_ent *entity2);
t_Vec2 	get_collisions(t_ent *e, t_mlx_data *mlx_data);
int 	is_ent_colliding(t_mlx_data *mlx_data, t_ent *e);

// MOUSE
void	update_mouse(t_mlx_data *mlx_data);

#endif