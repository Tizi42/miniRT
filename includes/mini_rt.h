/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:47:04 by tyuan             #+#    #+#             */
/*   Updated: 2021/01/01 16:52:50 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0

# define SPHERE 1
# define PLANE 2
# define SQUARE 3
# define CYLINDER 4
# define TRIANGLE 5
# define PYRAMID 6
# define CUBE 7
# define DISK 8

# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_BUTTON_PRESS 4
# define EVENT_BUTTON_RELEASE 5
# define EVENT_RED_CROSS 17

# define KEY_ESC 53
# define KEY_A 0
# define KEY_C 8
# define KEY_D 2
# define KEY_S 1
# define KEY_W 13
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_P 35
# define KEY_U 32
# define KEY_Q 12
# define KEY_K 40
# define KEY_J 38
# define KEY_L 37
# define KEY_I 34
# define KEY_M 46
# define KEY_H 4
# define KEY_Y 16

# define TRANS_SCALE 5
# define ROTATE_SCALE 10

# define THREAD_NB 0

typedef struct	s_uv
{
	double	u;
	double	v;
}				t_uv;

typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
	t_vec	i;
}				t_color;

typedef struct	s_checker
{
	int			width;
	int			height;
	t_color		color1;
	t_color		color2;
}				t_checker;

typedef struct	s_reso
{
	int			x;
	int			y;
	double		ratio;
}				t_reso;

typedef struct	s_image
{
	char		*add;
	void		*ptr;
	int			pixel_bits;
	int			line_bytes;
	int			endian;
}				t_image;

typedef struct	s_cam
{
	int			id;
	t_vec		pos;
	t_vec		dir;
	int			fov;
	t_image		img;
	t_vec		left;
	t_vec		right;
	t_vec		rotate_k0;
	double		rotate_a0;
	t_vec		rotate_k;
	double		rotate_angle;
}				t_cam;

typedef struct	s_light
{
	int			para;
	t_vec		pos;
	t_vec		dir;
	double		brightness;
	t_color		color;
	t_vec		i;
}				t_light;

typedef	struct	s_obj
{
	int			id;
	t_color		color;
	t_vec		pt;
	double		diameter;
	t_vec		ori;
	double		height;
	t_vec		pt2;
	t_vec		pt3;
	t_vec		norm;
	t_list		*list;
	int			select;
	int			hollow;
	t_checker	checker;
}				t_obj;

typedef struct	s_scene
{
	char		*name;
	int			save;
	void		*mlx_ptr;
	void		*win_ptr;
	t_reso		reso;
	t_light		amb;
	t_cam		*cam;
	t_light		*light;
	t_obj		*obj;
	t_list		*list_objs;
	t_list		*list_cams;
	t_list		*list_lights;
	int			cam_count;
	t_color		background_color;
}				t_scene;

typedef struct	s_thread
{
	int			x;
	t_scene		sc;
}				t_thread;

/*
**parse et main
*/
int				parse_getline(char *file, t_scene *sc);
void			parse_id(t_scene *sc, char *line);
void			parse_id2(t_scene *sc, char *line);
void			arguments_check(int ac, char **av, t_scene *sc);

/*
**parse_env
*/
char			*skip_spaces(char *line);
void			parse_reso(t_scene *sc, char *line);
void			parse_amb(t_scene *sc, char *line);
void			parse_cam(t_scene *sc, char *line);
void			parse_light(t_scene *sc, char *line);

/*
**parse_objects
*/
void			parse_sp(t_scene *sc, char *line);
void			parse_pl(t_scene *sc, char *line);
void			parse_sq(t_scene *sc, char *line);
void			parse_cy(t_scene *sc, char *line);
void			parse_tr(t_scene *sc, char *line);

/*
**parse_objects2
*/
void			parse_cu(t_scene *sc, char *line);
void			parse_py(t_scene *sc, char *line);
void			parse_disk(t_scene *sc, char *line);
void			parse_background_color(t_scene *sc, char *line);
char			*atoi_checker(char *line, t_scene *sc);

/*
**parse tool
*/
void			set_py(t_obj *py);
void			set_cu(t_obj *cu);
void			creat_cu_sqs(t_obj *cu, t_vec p[5]);
t_obj			*creat_sq(t_vec cen, t_vec ori, double side, t_color color);
t_obj			*creat_tr(t_vec pt, t_vec pt2, t_vec pt3, t_color color);

/*
**start_rt
*/
void			start_rt(t_scene *sc);
void			creat_image_for_all_cams(t_scene *sc);
void			ray_tracing(t_scene *sc);

/*
**start_rt_bonus
*/
void			ray_tracing_thread_b(t_thread *th);
void			ray_tracing_thread_a(t_scene *sc);

/*
**cam
*/
t_vec			get_cam_ray(int x, int y, t_scene *sc);
t_vec			rotation(t_vec pt, t_vec k, double angle);
void			set_cam(t_scene *sc);
void			change_cam(t_scene *sc);

/*
**hit
*/
void			intersect(t_vec ray_dir, t_scene *sc, int x, int y);
t_color			if_texture(t_obj obj, t_vec p);
t_vec			adjust_p_for_mapping(t_obj obj, t_vec p);
int				get_hit_point(t_vec ray_dir, double *t, t_scene *sc, t_vec pos);
int				hit_objects(t_vec ray_dir, double *t, t_obj *obj, t_vec cpos);

/*
**shadow
*/
int				is_shadow(t_scene sc, t_vec p);
int				is_shadow_para(t_scene sc, t_vec p);
t_vec			shadow_ray(t_vec ray_dir, t_scene sc, t_vec p);

/*
**hit_obj
*/
int				hit_sp(t_vec ray_dir, double *t, t_obj *sphere, t_vec cam_pos);
int				hit_pl(t_vec ray_dir, double *t, t_obj *plane, t_vec cam_pos);
int				hit_sq(t_vec ray_dir, double *t, t_obj *square, t_vec cam_pos);
int				hit_tr(t_vec ray_dir, double *t, t_obj *triangle, t_vec cpos);

/*
**hit_obj2
*/
int				hit_cy(t_vec ray_dir, double *t, t_obj *cy, t_vec cam_pos);
int				hit_cy_round(t_vec ray_dir, double *t, t_obj *cy, t_vec cpos);
int				hit_cy_caps(t_vec ray_dir, double *t, t_obj cy, t_vec cam_pos);
int				within_finite_cy(double t, t_obj cy, t_vec ray_dir, t_vec cpos);
void			get_cy_abc(double abc[3], t_vec ray_dir, t_obj *cy, t_vec cpos);

/*
**hit_obj3
*/
int				hit_py_cu(t_vec ray_dir, double *t, t_obj *py_cu, t_vec cpos);
int				hit_disk(t_vec ray_dir, double *t, t_obj disk, t_vec cam_pos);

/*
**color
*/
void			color_store(t_scene *sc, int x, int y, t_color color);
void			check_color_i(t_vec *i);
void			color_to_i(t_color *color);
t_color			i_to_color(t_color *color);
int				i_to_rgb(t_vec i);

/*
**bmp
*/
void			save_bmp(t_scene *sc);
void			bitmap_pixel_data(int fd, t_scene sc);
void			bitmap_file_header(int fd, t_scene sc);
void			bitmap_info_header(int fd, t_scene sc);
void			bitmap_info_header_2(int fd);

/*
**event exit
*/
void			error_handle(char *msg, t_scene *sc);
void			free_exit(t_scene *sc, int exit_id);
void			free_lst_py_cu(t_scene *sc);
void			free_img(t_scene *sc);
int				exit_hook(t_scene *sc);

/*
**event hook
*/
int				button_release_hook(int button, int x, int y, t_scene *sc);
int				key_release_hook(int keycode, t_scene *sc);
void			event_re_render(int keycode, t_scene *sc);
int				key_press_hook(int keycode, t_scene *sc);
void			select_type(int keycode, t_scene *sc);

/*
**event hook2
*/
void			move_obj(int keycode, t_scene *sc);
void			move_cam(int keycode, t_scene *sc);
void			select_obj(t_scene *sc, int id);
void			para_light_re_render(int keycode, t_scene *sc);
void			move_para_light(int keycode, t_scene *sc);

/*
**atoi 	tools
*/
char			*atoi_int(char *line, int *num, t_scene *sc);
char			*atoi_double(char *line, double *fnum, t_scene *sc);
char			*atoi_coordinates(char *line, t_vec *co, t_scene *sc);
char			*atoi_color(char *line, t_color *color, t_scene *sc);
char			*atoi_orient(char *line, t_vec *orient, t_scene *sc);

/*
**vec 	tools
*/
t_vec			vec_add(t_vec v1, t_vec v2);
t_vec			vec_sub(t_vec v1, t_vec v2);
t_vec			vec_mul(t_vec v, double m);
double			vec_dot(t_vec v1, t_vec v2);
t_vec			vec_mul_vec(t_vec v1, t_vec v2);

/*
**vec 2
*/
t_vec			vec_cross(t_vec v1, t_vec v2);
double			vec_length(t_vec v);
double			*vec_to_arr(t_vec s);
t_vec			get_vec(double a, double b, double c);

/*
**vec 3
*/
t_vec			normalize(t_vec v);
t_vec			get_surface_normal(t_obj obj, t_vec pt);

/*
**tools
*/
char			*get_bmp_file_name(char *sc_name, int count, t_scene *sc);
void			window_size_check(t_scene *sc);
int				solve_quadratic(double abc[3], double *t0, double *t1);
void			swap(double *t0, double *t1);
int				in_line(t_vec b, t_vec a, t_vec q, t_vec n);

/*
**tools2
*/
double			degree_to_radian(double degree);
double			max(double a, double b, double c);
void			find_square_side_vecs(t_obj *sq);
void			put_string_select(int id, t_scene sc);
void			set_side_for_sq(t_obj *sq, t_vec pt2, t_vec pt3);

/*
**tools3
*/
void			init_sc(t_scene *sc);
t_list			*find_obj_in_lst(t_list *list_objs, t_obj *obj);
int				lstiter_till_obj(t_list **lst, t_scene *sc);
int				move_obj_cy_sp(int keycode, t_scene *sc);

/*
**texture
*/
t_checker		uv_checkers(int width, int height, t_color c1, t_color c2);
t_color			pattern_at(int id, t_checker pattern, t_vec p);
t_color			uv_pattern_at(t_checker pattern, double u, double v);

/*
**texture uv map
*/
t_uv			spherical_map(t_vec p);
t_uv			planar_map(t_vec p);
t_uv			cylindrical_map(t_vec p);

#endif
