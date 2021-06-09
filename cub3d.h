/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:16:02 by hsamatha          #+#    #+#             */
/*   Updated: 2021/05/12 13:36:22 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_RIGHT				124
# define KEY_LEFT				123
# define KEY_ESC				53

# define RED  "\x1B[31m"
# define GRN  "\x1B[32m"
# define YEL  "\x1B[33m"
# define BLU  "\x1B[34m"

# define NORTH					0
# define SOUTH					1
# define WEST					2
# define EAST					3
# define SPRITE					4

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_point {
	int			x;
	int			y;
}				t_point;

typedef struct s_vector {
	double		x;
	double		y;
}				t_vector;

typedef struct s_pair {
	double		dist;
	int			order;
}				t_pair;

typedef struct s_color {
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_sprite {
	double		x;
	double		y;
}				t_sprite;

typedef struct s_image {
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			height;
	int			width;
}				t_image;

typedef struct s_map {
	t_color		floor_c;
	t_color		ceil_c;
	t_image		*t_arr;
	char		**text_path;
	char		**map;
	double		wall_x;
	double		step;
	double		text_pos;
	size_t		color;
	int			map_h;
	int			map_max_w;
	int			isplayer;
	int			text_count;
	int			tex_x;
	int			tex_y;
	int			scr_w;
	int			scr_h;
	int			h_atoi;
	int			w_atoi;
}				t_map;

typedef struct s_act {
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	transf;
	t_sprite	*spr_arr;
	t_sprite	cur_sp;
	t_point		draw_start;
	t_point		draw_end;
	t_point		tex;
	t_pair		*pair;
	double		*sp_buff;
	double		*sp_dist;
	double		inv_det;
	size_t		color;
	int			screen;
	int			count_spr;
	int			*sp_order;
	int			sp_screen_x;
	int			sp_height;
	int			sp_width;
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
}				t_act;

typedef struct s_mlx {
	void		*ptr;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_mlx;

typedef struct s_ray {
	t_vector	ray_dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	t_point		step;
	t_point		map;
	int			hit;
	int			side;
	int			line_h;
	int			draw_start;
	int			draw_end;
	double		camera_x;
	double		pwd;
	double		old_dir_x;
	double		old_plane_x;
}				t_ray;

typedef struct s_param {
	t_map	map;
	t_act	act;
	t_mlx	mlx;
	t_ray	ray;
}				t_param;

int		main(int argc, char **argv);
void	init_data(t_param *param);
void	get_texture(t_param *param);
int		get_next_line(int fd, char **line);
void	valid_texture(char flag, char *line, t_param *param);
int		pass_digits_space(char *line, int i);
void	start_mlx(t_param *param);
void	init_ray(t_ray *ray);
void	make_screenshot(t_param *param, char *name);
void	print_error(char *warn, char *text);
int		params_filled(t_param *param);
void	parse_map(int fd, t_param *param);
void	check_map_w(char *line, t_param *param);
char	**make_map(t_list **head, int size, t_param *param);
char	*fill_w_spaces(char *content, t_param *param);
void	valid_color(int n, char *line, int i, t_param *param);
int		movement(t_param *param);
void	double_check_c_param(int flag, t_param *param);
void	double_check_f_param(int f, t_param *param);
void	my_mlx_pixel_put(t_param *param, int x, int y, int color);
void	parse_we(char *line, t_param *param);
void	parse_ea(char *line, t_param *param);
void	parse_s(char *line, t_param *param);
void	parse_so(char *line, t_param *param);
void	parse_no(char *line, t_param *param);
void	parse_c(char *line, t_param *param);
void	parse_f(char *line, t_param *param);
void	check_forb_symb(char *line, int i, int flag);
int		pass_space(char *line, int i);
void	swe_player_checker(t_param *param, char sym);
int		create_trgb(int t, int r, int g, int b);
void	render(t_param *param, int x, int y);
int		ft_strlen(char *argv);
int		ft_atoi(const char *str, t_param *param, char ch);
void	*ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isdigit(int c);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
int		check_if_zero(int i);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
void	parse_res(char *line, t_param *param);
void	check_valid_symb(t_param *param, int i, int j, int flag);
void	check_space(t_param *param, int i, int j);
void	check_player(t_param *param, int i, int j);
void	check_border(t_param *param, int i, int j);
void	check_sprite(t_param *param, int i, int j);
void	render_sprites(t_param *param);
void	draw_pixel_spr(t_param *param, int stripe, int y);
void	sort_next(t_pair *arr, int start, int stop);
int		division(t_pair *arr, int start, int stop);
char	*ft_strjoin(char *s1, char *s2);
int		pass_space(char *line, int i);
char	*all_check(char **line, int fd, char **cache);
void	check_spr(t_param *param, int i, int j);
void	raycast(t_param *param, int x);
void	check_walls(t_param *param);
void	draw_pixel(t_param *param, int x);
void	def_texture(t_param *param);
void	sort_sprites(t_param *param, int sp_coun);
void	def_param_spr(t_param *param, int sp_coun);

#endif
