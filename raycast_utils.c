/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:17:08 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 14:01:48 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_walls(t_param *param)
{
	if (param->ray.side == 0)
		param->map.wall_x = param->act.pos.y
			+ param->ray.pwd * param->ray.ray_dir.y;
	else if (param->ray.side == 1)
		param->map.wall_x = param->act.pos.x + param->ray.pwd
			* param->ray.ray_dir.x;
	param->map.wall_x -= floor(param->map.wall_x);
	param->map.tex_x = (int)(param->map.wall_x
			*(double)(param->map.t_arr[param->map.text_count].width));
	if (param->ray.side == 1 && param->ray.ray_dir.y < 0)
		param->map.tex_x = param->map.t_arr
		[param->map.text_count].width - param->map.tex_x - 1;
	if (param->ray.side == 0 && param->ray.ray_dir.x > 0)
		param->map.tex_x = param->map.t_arr
		[param->map.text_count].width - param->map.tex_x - 1;
	param->map.step = 1.0 * param->map.t_arr
	[param->map.text_count].height / param->ray.line_h;
	param->map.text_pos = (param->ray.draw_start
			 - param->map.scr_h / 2 + param->ray.line_h / 2)
		 * param->map.step;
}

void	draw_pixel(t_param *param, int x)
{
	int	y;

	y = param->ray.draw_start - 1;
	while (y++ < param->ray.draw_end)
	{
		param->map.tex_y = (int)param->map.text_pos
			& (param->map.t_arr[param->map.text_count].height - 1);
		param->map.text_pos += param->map.step;
		param->map.color = *(unsigned int *)
			(param->map.t_arr[param->map.text_count].addr
				+ (param->map.tex_y
					* param->map.t_arr[param->map.text_count].line_len
					+ param->map.tex_x
					* (param->map.t_arr[param->map.text_count].bpp
						 / 8)));
		my_mlx_pixel_put(param, param->map.scr_w - x - 1, y,
			param->map.color);
	}
	param->act.sp_buff[x] = param->ray.pwd;
}

void	def_texture(t_param *param) //define wall depending on the pos
{
	if (param->ray.side == 1)
	{
		if (param->ray.ray_dir.y < 0)
			param->map.text_count = NORTH;
		else if (param->ray.ray_dir.y > 0)
		{
			if (param->ray.ray_dir.x != 0)
				param->map.text_count = SOUTH;
		}
	}
	else if (param->ray.side == 0)
	{
		if (param->ray.ray_dir.x < 0 && param->ray.ray_dir.y != 0)
			param->map.text_count = WEST;
		if (param->ray.ray_dir.x >= 0)
		{
			if ((param->ray.ray_dir.y != 0
					 && param->ray.ray_dir.x != 0)
				 || param->ray.ray_dir.y < 0)
				param->map.text_count = EAST;
		}
	}
}

void	draw_pixel_spr(t_param *param, int stripe, int y)
{
	param->act.tex.x = (int)(256 * (stripe - (-param->act.sp_width
					/ 2 + param->act.sp_screen_x))
			 * param->map.t_arr[SPRITE].width
			/ param->act.sp_width) / 256;
	if (param->act.transf.y > 0 && stripe > 0
		&& stripe < param->map.scr_w
		&& param->act.transf.y < param->act.sp_buff[stripe])
	{
		y = param->act.draw_start.y - 1;
		while (++y < param->act.draw_end.y)
		{
			param->act.d = y * 256 - param->map.scr_h
				* 128 + param->act.sp_height * 128;
			param->act.tex.y = ((param->act.d * param->map.t_arr
					[SPRITE].height) / param->act.sp_height) / 256;
			param->act.color = *(unsigned int *)
				(param->map.t_arr[SPRITE].addr + (param->act.tex.y
						 * param->map.t_arr[SPRITE].line_len
						+ param->act.tex.x
						* (param->map.t_arr[SPRITE].bpp / 8)));
			if ((param->act.color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(param, param->map.scr_w
					- stripe - 1, y, param->act.color); //put pixel
		}
	}
}

void	sort_next(t_pair *arr, int start, int stop)
{
	int	pivot_index;

	if (start < stop)
	{
		pivot_index = division(arr, start, stop);
		sort_next(arr, start, pivot_index - 1);
		sort_next(arr, pivot_index + 1, stop);
	}
}
