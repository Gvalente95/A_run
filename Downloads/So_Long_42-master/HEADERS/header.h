/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:32:42 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/19 13:00:09 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include "colors.h"
# include "audio.h"
# include <mlx.h>
# include "Keys.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <time.h>
# include <fcntl.h>

# define BGR_SPRITE_PATH "PNG/BGRND/"

# define PLAYER_SPR_PATH 		"PNG/ENTITIES/PLAYER/"
# define MOB_SPR_PATH 			"PNG/ENTITIES/MOBS/"

# define WALL_SPR_PATH 			"PNG/WALL/"
# define GROUND_SPR_PATH 		"PNG/GROUND/"
# define GROUND_TILESET_PATH	"PNG/GROUND/8_sliced/"

# define BUSH_SPR_PATH 			"PNG/BUSH/"
# define TREES_SPR_PATH 		"PNG/TREES/"
# define ROAD_SPR_PATH 			"PNG/ROAD/"
# define TILES_SPR_PATH 		"PNG/TILES/"
# define COIN_SPR_PATH 			"PNG/COLLECTIBLES/COIN/"
# define KEY_SPR_PATH 			"PNG/COLLECTIBLES/KEY/"
# define DOOR_SPR_PATH 			"PNG/DOOR/"
# define PORTAL_SPR_PATH 		"PNG/PORTAL/"
# define AXE_SPR_PATH 			"PNG/COLLECTIBLES/PICKAXE/"

# define WIN_W 				1400
# define WIN_H 				1000
# define MOB_AMOUNT 		10
# define COIN_AMOUNT 		10
# define ENV_AMOUNT 		50
# define READ_BUFFER_SIZE 	50
# define MV_DUR 			30
# define PLAYER_SPEED 		2
# define MOBS_SPD 			2
# define ANIM_REFRESH		5
# define CAT_COUNT 			7

# define LEFT_UP			0
# define UP 				1
# define RIGHT_UP			2
# define LEFT				3
# define CENTER				4
# define RIGHT				5
# define DOWN_LEFT			6
# define DOWN				7
# define DOWN_RIGHT			8

typedef enum e_dir
{
	up,
	left,
	down,
	right,
	none,
	DIR_LEN
}	t_dir;

# define TYPESTR "PMCKDE1AGBTV"

typedef enum e_entity_types
{
	player,
	mob,
	coin,
	key,
	door,
	portal,
	wall,
	axe,
	ground,
	bgrnd,
	tile,
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
}	t_vec2;

typedef struct s_Vector3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_input
{
	char	*buffer;
	int		index;
}	t_input;

typedef struct s_map
{
	t_vec2	size;
	t_vec3	pos;
	char	*buffer;
	char	*name;
	int		len;
	int		mob_max;
	int		coin_max;
	int		coins_amount;
	int		tries_amount;
}	t_map;

typedef struct s_image_data
{
	t_vec2	pos;
	t_vec2	size;
	void	*dest;
	double	x_ratio;
	double	y_ratio;
	int		*src_data;
	int		*dst_data;
	int		bpp;
	int		len;
	int		bps;
	int		endian;
	int		*scl_d;
}	t_image;

typedef struct s_entity
{
	t_ent_type		type;
	t_ent_action	action;
	t_dir			dir;
	t_vec2			start_pos;
	t_vec3			prv_pos;
	t_vec3			base_pos;
	t_vec3			pos;
	t_vec2			size;
	t_vec2			foll_ofs;
	t_vec3			movement;
	char			*frame_path;
	void			*cur_frame;
	void			*cur_frame_x;
	void			**anim_frames;
	void			**wlk_frm;
	void			**idl_frm;
	void			**fly_frm;
	void			**wlk_frm_x;
	void			**idl_frm_x;
	void			**fly_frm_x;
	int				hurt_timer;
	int				is_active;
	int				foll_spd;
	int				walk_frame_amount;
	int				idle_frame_amount;
	int				frames_amount;
	int				hp;
	int				is_grounded;
	int				jumps;
	int				jump_timer;
	int				flip_x;
	int				jet_sky_timer;
	int				cur_frame_index;
}	t_ent;

typedef struct s_md
{
	t_map		map;
	t_ent		*key;
	t_ent		*pickaxe;
	t_ent		*bgrnd;
	t_ent		**images;
	t_ent		**bg_env;
	t_ent		plr;
	t_ent		*exit;
	t_vec3		ext_p;
	pid_t		bgrnd_au;
	t_ent		*sel;
	t_ent		*selected;
	t_ent		**all_images;
	t_vec3		mouse_pos;
	char		**coin_paths;
	char		**ftstp_paths;
	void		*mlx;
	void		*win;
	void		*bg_col;
	void		*bgrnd_img;
	void		**env_images;
	int			index;
	int			move_counter;
	int			cur_category;
	int			has_key;
	int			ftstp_timer;
	int			key_prs[512];
	int			key_clicked;
	int			mouse_pressed;
	int			mouse_clicked;
	int			coins_amount;
	int			images_len;
	int			bg_env_len;
	int			t_len;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			time;
	int			save_mode;
	char		*addr;
}	t_md;

// INIT
void	init_game(t_md *md);
t_ent	*init_entity(t_md *md, void *frames_path, t_vec3 pos, t_vec3 values);
int		init_player(t_md *md, char *frames_path, t_vec3 pos);
int		init_mlx(t_md *md);
// UPDATE
int		update(t_md *md);
void	update_env(t_md *md);
// RENDER
void	render_player(t_md *md);
void	render(t_md *md);
void	render_text(t_md *md, t_vec2 pos, const char *format, ...);
// INPUT
int		handle_key_release(int keycode, t_md *md);
int		handle_key_press(int keycode, t_md *md);
// LEVEL
void	load_new_level(t_md *md);
char	*generate_map(t_map *map, int max_try, int solvable);
// IMAGE
void	*add_img(char *relative_path, int *width, int *height, void *mlx);
void	my_mlx_pixel_put(t_md *data, int x, int y, int color);
void	**get_images(t_md *d, t_ent *e, char **paths, t_vec2 size);
void	*get_image_copy(t_md *mlx_ptr, void *src, t_vec2 src_size);
void	*scale_img(void *mlx, void *img, t_vec2 *old_size, t_vec2 new_size);
// TOOLS
char	**get_paths(char *path, char *prefix, int amount, char *suffix);
int		r_range(int min, int max);
void	*flip_image_x(void *mlx, void *img, t_vec2 size);
void	render_array(t_md *md, t_ent **e, int len, int show_portal);
int		get_array_size(void **array);
void	relaunch_program(const char *arg);
int		contain(char c, char *arg);
// COLLISIONS
t_vec2	get_collision_displacement(t_ent *e1, t_ent *e2, int e2_i, t_vec2 d);
t_vec2	get_collisions(t_ent *e, t_ent **col_ents, t_vec2 displ);
int		is_in_pos(t_vec3 pos1, t_vec2 size1, t_vec3 pos2, t_vec2 size2);
void	set_vec_to_dir(t_dir dir, t_vec3 *vec, int mv_am);
// DELETE
int		del_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, int *e_len);
int		delete_type(t_ent_type type, t_ent **ents, int *ents_len);
int		move_to(t_ent *e, t_vec3 target_pos, t_vec2 spd_limits, int range);
int		is_in_pos(t_vec3 pos1, t_vec2 size1, t_vec3 pos2, t_vec2 size2);
//VECTORS
int		set_vec2(t_vec2 *Vec2, int x, int y);
int		set_vec3(t_vec3 *Vec3, int x, int y, int z);
t_vec2	get_vec2(int x, int y);
t_vec3	get_vec3(int x, int y, int z);
t_vec3	get_grid_pos(t_md *md, t_vec3 p);
// MOUSE
void	init_mouse(t_md *md);
void	update_mouse(t_md *md);
void	set_ent_to_mouse(t_ent *ent, t_md *md);
// MLX
void	reset_mlx_values(t_md *md);
// ENTITIES
t_ent	*copy_ent(t_ent *e);
t_ent	*get_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, int len);
void	sort_ents_by_z(t_ent **game_entities, int count);
void	swap_game_entities(t_ent *a, t_ent *b);
void	increment_frame(t_ent *e);
int		delete_at_index(int index, t_ent **ents, int len);
// PARSING
t_vec2	get_map_dimensions(char *map, int i, int current_width, t_vec2 res);
t_ent	*parse_letter(t_md *md, t_vec3 pos, char c, int scale);
t_ent	*parse_letter(t_md *md, t_vec3 pos, char c, int scale);
void	load_valid_map(char *file_path, t_md *md, char *buffer, t_vec2	pos);
void	get_ents_from_map(t_md *md, int i, t_vec3 pos);
char	*get_new_map(int width, int height, int solvable);
char	*get_next_line(int fd);
// MOVEMENT
int		handle_movement(t_md *md, t_ent *e, t_vec2 base_speed, t_vec2 displ);
int		move_to_simple(t_ent *e, t_vec3 targ_pos, int spd);
// CHECKER
t_vec2	get_map_dimensions(char *map, int i, int current_width, t_vec2 res);
t_vec2	get_indexes(char *buffer);
int		propagate_search(t_vec2 *indexes, char *buff, int line_width);
int		check_neighbors(char *buff, int ind, int end_index, int wd);
int		verify_map_borders(char *buffer, int width, int height);
char	*get_map_buffer(int fd, int check_for_errors);
int		close_and_quit(char *error_msg, int fd);
// AUDIO
pid_t	play_sound(const char *filename, int loop);
void	stop_sound(pid_t pid);
pid_t	play_random_sound(const char *path, int len, const char *format);
int		is_audio_playing(pid_t pid);

void	update_coin_entity(t_ent *e, t_md *md, int range, int index);

// ENT TOOLS
int		destroy_if_reached(t_ent *e, t_md *md, t_vec2 targ_size, t_vec3 p);
void	update_circular_motion(t_ent *e, t_md *md);
int		move_ent_towards(t_ent *e, t_md *md, t_vec3 p, int range);
void	update_collectible(t_ent *e, t_md *md, int range, int index);
int		has_ent_moved(t_ent e);
t_ent	*get_ent_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, t_ent_type type);
int		get_distance(t_ent a, t_ent b);

void	handle_entity_frames(t_md *md, t_ent *e, void *path, t_vec2 scale);
void	init_player_frames(t_md *md, char *path, t_ent *e);

int		check_path_format(char *path);
t_ent	*get_ent_simple(t_vec2 pos, t_ent **ents);

void	remap_wall_entities(t_md *md, t_ent *e, char *png_path, t_vec3 pos);
void	load_env_elements(t_md *md);
void	free_array(t_ent **ents, int len, int i);
void	load_images(t_md *md);
int		save_to_file(t_md *md);
int		update_editor(t_md *md);
char	map_keycode_to_char(int keycode);
char	*store_map_name(t_md *md);
int		free_md(t_md *md);
int		free_void(void *elem);
int		free_void_array(void **elements, int i);
#endif