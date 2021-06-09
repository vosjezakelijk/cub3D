/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:09:06 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 13:47:02 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map(t_map *map)
{
	map->scr_w = 0;
	map->scr_h = 0;
	map->floor_c.r = -1;
	map->floor_c.g = -1;
	map->floor_c.b = -1;
	map->ceil_c.r = -1;
	map->ceil_c.g = -1;
	map->ceil_c.b = -1;
	map->map = NULL;
	map->map_h = 0;
	map->map_max_w = 0;
	map->isplayer = 0;
	map->text_count = 0;
	map->wall_x = 0;
	map->tex_x = 0;
	map->tex_y = 0;
	map->step = 0;
	map->text_pos = 0;
	map->color = 0;
	map->h_atoi = 0;
	map->w_atoi = 0;
}

static void	init_map_malloc(t_map *map)
{
	int	i;

	i = 0;
	map->t_arr = malloc(5 * sizeof(t_image));
	map->text_path = malloc(5 * sizeof(char *));
	if (map->t_arr == NULL || map->text_path == NULL)
		print_error("Error", "Memory error in init");
	while (i < 5)
	{
		map->t_arr[i].img = NULL;
		map->t_arr[i].addr = NULL;
		map->t_arr[i].line_len = 0;
		map->t_arr[i].endian = 0;
		map->t_arr[i].bpp = 0;
		map->t_arr[i].height = 0;
		map->t_arr[i].width = 0;
		map->text_path[i] = NULL;
		i++;
	}
}

static void	init_act(t_act *act)
{
	act->pos.x = 0;
	act->pos.y = 0;
	act->dir.x = 0;
	act->dir.y = 0;
	act->plane.x = 0;
	act->plane.y = 0;
	act->count_spr = 0;
	act->pair = NULL;
	act->w = 0;
	act->s = 0;
	act->a = 0;
	act->d = 0;
	act->left = 0;
	act->right = 0;
}

void	init_data(t_param *param)
{
	init_map(&(param->map));
	init_map_malloc(&(param->map));
	init_act(&(param->act));
	init_ray(&(param->ray));
	param->mlx.win = NULL;
	param->mlx.img = NULL;
	param->mlx.addr = NULL;
	param->mlx.bpp = 0;
	param->mlx.line_len = 0;
	param->mlx.endian = 0;
	param->mlx.ptr = mlx_init(); // for mlx lib
}

void	get_texture(t_param *param)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		param->map.t_arr[i].img = mlx_png_file_to_image(
				param->mlx.ptr,
				param->map.text_path[i],
				&param->map.t_arr[i].width,
				&param->map.t_arr[i].height);
		param->map.t_arr[i].addr = mlx_get_data_addr(
				param->map.t_arr[i].img,
				&(param->map.t_arr[i].bpp),
				&(param->map.t_arr[i].line_len),
				&(param->map.t_arr[i].endian));
		i++;
	}
	param->act.sp_dist = malloc(param->act.count_spr * sizeof(double));
	param->act.sp_buff = malloc((param->map.scr_w) * sizeof(double));
	param->act.sp_order = malloc(param->act.count_spr * sizeof(int));
	if (!param->act.sp_order && !param->act.sp_buff && param->act.sp_dist)
		print_error("Error", "Memory allocation error");
}
