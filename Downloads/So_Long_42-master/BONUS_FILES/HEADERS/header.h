/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:32:42 by gvalente          #+#    #+#             */
/*   Updated: 2024/11/22 02:01:35 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include "audio.h"
# include "colors.h"
# include <mlx.h>
# include "Keys.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <time.h>
# include <fcntl.h>

# define BGR_SPRITE_PATH "PNG/BGRND/"

# define SCRN_WIDTH 1440
# define SCRN_HEIGHT 840

# define PLAYER_SPR_PATH 		"PNG/ENTITIES/PLAYER/"
# define MOB_SPR_PATH 			"PNG/ENTITIES/MOBS/"

# define PARTICLE_SPR_PATH		"PNG/PARTICLES/"
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
# define RECT_SQUARE			"PNG/SQUARE.png"

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
# define PRT_PNGS_LEN		16
# define PRT_AMOUNT			50

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
	particle,
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

typedef enum e_particle_tpes
{
	proj,
	splat,
	fly,
	target,
	circle,
	trail,
}	t_prt_type;

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

typedef struct s_particle
{
	t_prt_type	type;
	t_vec2		foll_ofs;
	t_vec2		pos;
	t_vec2		size;
	t_vec2		movement;
	t_vec2		*target_pos;
	t_dir		dir;
	void		*cur_frame;
	int			is_grounded;
	int			lifetime;
	int			is_active;
	int			speed;
}	t_prt;

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
	t_prt_type		prt_type;
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
	t_prt		**particles;
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
	pid_t		jump_audio_played;
	pid_t		d_jump_audio_played;
	int			focused;
	int			coin_au_timer;
	void		*mlx;
	void		*win;
	void		*bg_col;
	void		*bgrnd_img;
	void		**env_images;
	int			particles_alive;
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

//PARTICLES
int		init_particles(t_md *md, int i, t_vec2 size, t_prt *p);
int		reset_particle(t_md *md, t_prt *p, int index);
int		activate_particle(t_md *md, t_prt *p, t_vec3 pos, t_prt_type type);
int		set_particles(t_md *md, int amount, t_vec3 pos, t_prt_type type);
int		update_particle(t_md *md, t_prt *p, int index);
void	update_particles(t_md *md);
int		handle_prt_movement(t_md *md, t_prt *p, t_vec2 cols);
t_vec2	set_prt_movement(t_vec3 pos, t_vec3 target, t_prt *prt);
int		free_particles(t_md *md, t_prt **prts);

// 		INIT
void	init_game(t_md *md);
void	init_mouse(t_md *md);
int		init_player(t_md *md, char *frames_path, t_vec3 pos);
int		init_mlx(t_md *md, int i);
void	init_window(t_md *md);
void	init_bgrnd(t_md *md, t_vec2 size);
t_ent	*init_entity(t_md *md, void *frames_path, t_vec3 pos, t_vec3 values);

// 		UPDATE
int		update(t_md *md);
void	update_mouse(t_md *md);
int		update_editor(t_md *md);
void	update_env(t_md *md, int i);
void	update_circular_motion(t_ent *e, t_md *md);
void	update_collectible(t_ent *e, t_md *md, int range, int index);
void	update_coin_entity(t_ent *e, t_md *md, int range);
t_vec3	update_key_entity(t_md *md, t_ent *e, t_vec3 targ_pos);

// 		RENDER
void	render_player(t_md *md);
void	render(t_md *md);
void	render_text(t_md *md, t_vec2 pos, const char *format, ...);
void	render_game_values(t_md *md);

// 		INPUT
int		handle_key_release(int keycode, t_md *md);
int		handle_key_press(int keycode, t_md *md);
char	map_keycode_to_char(int keycode);

// 		LEVEL
void	load_new_level(t_md *md);
char	*generate_map(t_map *map, int max_try, int solvable);
char	*get_empty_map(t_vec2 map_size);
int		save_to_file(t_md *md);
char	*store_map_name(t_md *md);

// 		IMAGE
void	*add_img(char *relative_path, int *width, int *height, void *mlx);
void	my_mlx_pixel_put(t_md *data, int x, int y, int color);
void	**get_images(t_md *d, t_ent *e, char **paths, t_vec2 size);
void	*get_image_copy(t_md *mlx_ptr, void *src, t_vec2 src_size);
void	*scale_img(void *mlx, void *img, t_vec2 *old_size, t_vec2 new_size);

// 		TOOLS
char	**get_paths(char *path, char *prefix, int amount, char *suffix);
int		r_range(int min, int max);
void	*flip_image_x(void *mlx, void *img, t_vec2 size);
void	render_array(t_md *md, t_ent **e, int show_portal, int i);
int		get_array_size(void **array);
void	relaunch_program(const char *arg);
int		contain(char c, char *arg);
void	reset_mlx_values(t_md *md);

//		POSITION
int		is_in_pos(t_vec3 pos1, t_vec2 size1, t_vec3 pos2, t_vec2 size2);
t_vec3	get_grid_pos(t_md *md, t_vec3 p);
void	set_target_position(t_vec3 *p, t_vec2 *target_size, \
	t_md *md, t_ent *target);

// 		MOVEMENT
t_vec2	handle_movement(t_md *md, t_ent *e, t_vec2 base_speed, t_vec2 displ);
int		move_to(t_ent *e, t_vec3 target_pos, t_vec2 spd_limits, int range);
int		move_to_simple(t_ent *e, t_vec3 targ_pos, int spd);

// 		COLLISIONS
t_vec2	get_collision_displacement(t_ent *e1, t_ent *e2, int e2_i, t_vec2 d);
t_vec2	get_collisions(t_md *md, t_ent *e, t_ent **col_ents, t_vec2 displ);
void	set_vec_to_dir(t_dir dir, t_vec3 *vec, int mv_am);

//		VECTORS
t_vec2	get_vec2(int x, int y);
t_vec3	get_vec3(int x, int y, int z);
int		set_vec2(t_vec2 *Vec2, int x, int y);
int		set_vec3(t_vec3 *Vec3, int x, int y, int z);
int		get_distance(t_vec3 a, t_vec3 b);

// 		DELETE
int		del_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, int *e_len);
int		delete_type(t_ent_type type, t_ent **ents, int *ents_len);
int		delete_at_index(int index, t_ent **ents, int len);

//		ENTITIES
t_ent	*get_ent_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, t_ent_type type);
t_ent	*get_ent_simple(t_vec2 pos, t_ent **ents);
t_ent	*get_at_pos(t_vec3 pos, t_vec2 size, t_ent **ents, int len);
t_ent	*copy_ent(t_ent *e);
void	sort_ents_by_z(t_ent **game_entities, int count);
void	swap_game_entities(t_ent *a, t_ent *b);
void	increment_frame(t_ent *e);
void	set_ent_to_mouse(t_ent *ent, t_md *md);
void	insert_entity(t_vec3 pos, t_ent *to_insert, t_ent ***arr, int *len);
int		hurt_entity(t_md *md, t_ent *e, char *hit_path, char *kill_path);
int		move_ent_towards(t_ent *e, t_md *md, t_vec3 p, int range);

//		PARSING
t_vec2	get_map_dimensions(char *map, int i, int current_width, t_vec2 res);
t_ent	*parse_letter(t_md *md, t_vec3 pos, char c, int scale);
t_ent	*parse_letter(t_md *md, t_vec3 pos, char c, int scale);
char	*get_new_map(int width, int height, int solvable);
char	*get_next_line(int fd);
void	load_valid_map(char *file_path, t_md *md, char *buffer, t_vec2	pos);
void	load_ents(t_md *md, int i, t_vec3 pos);
void	load_env_elements(t_md *md);
void	load_images(t_md *md);
void	load_ents_editor(t_md *md, int i, t_vec3 pos);

//		CHECKER
t_vec2	get_map_dimensions(char *map, int i, int current_width, t_vec2 res);
t_vec2	get_indexes(char *buffer);
char	*get_map_buffer(int fd, int check_for_errors);
int		propagate_search(t_vec2 *indexes, char *buff, int line_width);
int		check_neighbors(char *buff, int ind, int end_index, int wd);
int		verify_map_borders(char *buffer, int width, int height);
int		close_and_quit(char *error_msg, int fd);

//		AUDIO
pid_t	play_sound(const char *filename, int loop);
pid_t	play_random_sound(const char *path, int len, const char *format);
void	stop_sound(pid_t pid);
int		is_audio_playing(pid_t pid);

//		ANIMATION
void	handle_entity_frames(t_md *md, t_ent *e, void *path, t_vec2 scale);
void	init_player_frames(t_md *md, char *path, t_ent *e);
int		check_path_format(char *path);
void	remap_wall_entities(t_md *md, t_ent *e, char *png_path, t_vec3 pos);

//		FREE
int		free_md(t_md *md);
int		free_void(void *elem);
int		free_void_array(void **elements, int i);
void	free_array(t_ent **ents, int len, int i);

#endif