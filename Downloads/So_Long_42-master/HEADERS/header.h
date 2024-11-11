/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:32:42 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/11 13:06:59 by giuliovalen      ###   ########.fr       */
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
# include <fcntl.h>
# include "colors.h"

# define BACKGROUND_SPRITE_PATH "RESSOURCES/PNG/BACKGROUND/"

# define WALL_SPRITES_PATH "RESSOURCES/PNG/WALL/"
# define GROUND_SPRITES_PATH "RESSOURCES/PNG/GROUND/"
# define BUSH_SPRITES_PATH "RESSOURCES/PNG/BUSH/"
# define TREES_SPRITES_PATH "RESSOURCES/PNG/TREES/"
# define ROAD_SPRITES_PATH "RESSOURCES/PNG/ROAD/"
# define TILES_SPRITES_PATH "RESSOURCES/PNG/TILES/"
# define COLLECTIBLES_SPRITES_PATH "RESSOURCES/PNG/COLLECTIBLES/"
# define PORTAL_SPRITES_PATH "RESSOURCES/PNG/PORTAL/"

# define PLAYER_SPRITES_PATH "RESSOURCES/PNG/ENTITIES/PLAYER/"
# define MOB_SPRITES_PATH "RESSOURCES/PNG/ENTITIES/MOBS/"

# define PLAYER_IDLE_0 "RESSOURCES/PNG/ENTITIES/PLAYER/IDLE_0.png"
# define PLAYER_IDLE_1 "RESSOURCES/PNG/ENTITIES/PLAYER/IDLE_1"
# define PLAYER_WALK_0 "RESSOURCES/PNG/ENTITIES/PLAYER/WALK_0"
# define PLAYER_WALK_1 "RESSOURCES/PNG/ENTITIES/PLAYER/WALK_1"

# define GROUND_0 "RESSOURCES/PNG/TILES/0"
# define WALL_0 "RESSOURCES/PNG/TILES/0"
# define TEST_IMG "RESSOURCES/PNG/BUSH/0.png"

# define RESIZE 1.5
# define WIN_W 	1980
# define WIN_H 	1080
# define MOB_AMOUNT 	10
# define COIN_AMOUNT 10
# define ENV_AMOUNT 50
# define READ_BUFFER_SIZE 50
# define GROUND_LEVEL 880
# define MV_DUR 30
# define MV_AM 2
# define PLAYER_SPEED 2
# define MOBS_SPD 2
# define ANIM_REFRESH 5
# define CAT_COUNT 7
# define ARRAY_MAX 200

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
	exitance,
	env,
	wall,
	ground,
	background,
	trees,
	deco,
	tile,
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
}	t_vec2;

typedef struct s_Vector3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_entity
{
	char			*frame_path;
	void			*cur_frame;
	void			*cur_frame_x;
	void			**anim_frames;
	void			*wlk_frm[3];
	void			*idl_frm[3];
	void			*wlk_frm_x[3];
	void			*idl_frm_x[3];
	int				walk_frame_amount;
	int				idle_frame_amount;
	int				frames_amount;
	int				hp;
	int				has_col;
	int				is_grounded;
	int				jumps;
	int				flip_x;
	int				jump_timer;
	int				jet_sky_timer;
	int				cur_frame_index;
	t_ent_type		type;
	t_ent_action	action;
	t_dir			dir;
	t_vec3			prv_pos;
	t_vec3 			base_pos;
	t_vec3			pos;
	t_vec2			size;
	t_vec2			follow_ofs;
	t_vec3			movement;
}	t_ent;

typedef struct s_mlx_data
{
	t_vec3		size;
	t_ent		*game_entities[ENV_AMOUNT];
	t_ent		**env;
	t_ent		**game_mobs;
	t_ent		player;
	t_ent		*selected;
	t_ent		***alll_images;
	t_ent		*background;
	t_ent		**images;
	int			cur_array_size;
	int			images_len;
	int			cur_category;
	int			clicked;
	int			key_state[512];
	int			last_key_pressed;
	void		*mlx;
	void		*win;
	void		*background_color;
	void		*background_img;
	void		*ground;
	void		*tiles;
	char		*addr;
	int			mouse_prv;
	int			mouse_button;
	int			mouse_pos[2];
	int			god_mode;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			time;
}				t_mlx_data;

// INIT
int		init_mlx_data(t_mlx_data *mlx_data, t_vec2 win_size);
int		init_game_entities(t_mlx_data *mlx_data);
int		init_player(t_mlx_data *mlx_data, char *frames_path, t_vec3 pos);
t_ent	*init_entity(t_mlx_data *mlx_data, void *frames_path, t_vec3 pos, t_vec3 values);
// UPDATE
int		update(t_mlx_data *mlx_data);
// RENDER
void	render_images(t_mlx_data *mlx_data);
void	render_player(t_mlx_data *mlx_data);

// IMAGE
void	*add_img(char *relative_path, int *width, int *height, void *mlx);
void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
int		set_entity_frames(t_mlx_data *d, t_ent *e, char **WLK_P, char **IDLE_P);
void	set_img_color(t_vec2 size, void *frame, int new_color, float intensity);
void	*get_image_copy(t_mlx_data *mlx_ptr, void *src, t_vec2 src_size);
void	*rescale_image(void *mlx, void *img, t_vec2 *old_size, t_vec2 new_size);

// INPUT
int		handle_key_release(int keycode, t_mlx_data *mlx_data);
int		handle_key_press(int keycode, t_mlx_data *mlx_data);
// TOOLS
void 	sort_game_entities_by_z_pos(t_ent **game_entities, int count);
char	**get_frames_paths(char *path, char *suffix, int amount);
int		rand_range(int min, int max);
void	*flip_image_x(void *mlx, void *img, int width, int height);
void 	render_entity(t_mlx_data *mlx_data, t_ent *e);
void 	render_array(t_mlx_data *mlx_data, t_ent **e, t_ent *selected);
int 	get_array_size(void **array);

//STUFF
int		get_trgb(unsigned char t, unsigned char r, unsigned char g, \
		unsigned char b);
void 	set_brightness(int width, int height, void *frame, float factor);

// COLLISIONS
t_vec2 	get_collision_displacement(t_ent *entity1, t_ent *entity2, int entity2_index);
t_vec2 	get_collisions(t_ent *e, t_ent **col_ents);
int 	is_in_pos(t_vec3 pos1, t_vec2 size1, t_vec3 pos2, t_vec2 size2);
int 	delete_ents_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, int *ents_len);
int 	delete_type(t_ent_type type, t_ent **ents, int *ents_len);

//VECTORS
int		set_Vec2(t_vec2 *Vec2, int x, int y);
int		set_Vec3(t_vec3 *Vec3, int x, int y, int z);
char	print_Vec3(t_vec3 Vec3);
t_vec3	rand_Vec3(int min, int max);
t_vec2 	get_Vec2(int x, int y);
t_vec3 	get_Vec3(int x, int y, int z);

// MOUSE
void 	init_mouse(t_mlx_data *mlx_data);
void	update_mouse(t_mlx_data *mlx_data);
void 	set_ent_to_mouse(t_ent *ent, t_mlx_data *mlx_data);

// MAP EDITOR
void 	load_images(t_mlx_data *mlx_data);
void 	set_new_category(t_mlx_data *mlx_data, int new_cat, int cur_index);
int 	render_map_images(t_mlx_data *mlx_data);
// MLX
void 	reset_mlx_values(t_mlx_data *mlx_data);

// ENTITIES
t_ent 	*copy_ent(t_ent *e);
t_ent 	**get_ents_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, int ents_len);
void 	swap_game_entities(t_ent *a, t_ent *b);
char	*get_next_line(int fd);
int 	delete_at_index(int index, t_ent **ents, int len);
t_ent 	*get_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, int len);

// PARSEFILE
int load_from_file(t_mlx_data *mlx_data, char *file_path);
int save_to_file(t_mlx_data *mlx_data, int len);

int render_map_images(t_mlx_data *mlx_data);

int move_towards(t_ent *e, t_vec3 target_pos, int min_speed, int max_speed, int aggro_range);

#endif