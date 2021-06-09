/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:09:30 by hsamatha          #+#    #+#             */
/*   Updated: 2021/05/12 13:42:27 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	key_sd(t_param *param, double move)
{
	if (param->act.s == 1)
	{
		if (param->map.map[(int)(param->act.pos.y)][(int)(param->act.pos.x - param->act.dir.x * move)] != '1')
			param->act.pos.x -= param->act.dir.x * move;
		if (param->map.map[(int)(param->act.pos.y - param->act.dir.y * move)][(int)(param->act.pos.x)] != '1')
			param->act.pos.y -= param->act.dir.y * move;
	}
	if (param->act.d == 1)
	{
		if (param->map.map[(int)(param->act.pos.y)][(int)(param->act.pos.x - param->act.plane.x * move)] != '1')
			param->act.pos.x -= param->act.plane.x * move;
		if (param->map.map[(int)(param->act.pos.y - param->act.plane.y * move)][(int)(param->act.pos.x)] != '1')
			param->act.pos.y -= param->act.plane.y * move;
	}
}

static void	key_wa(t_param *param, double move)
{
	if (param->act.w == 1)
	{
		if (param->map.map[(int)(param->act.pos.y)][(int)(param->act.pos.x + param->act.dir.x * move)] != '1')
			param->act.pos.x += param->act.dir.x * move;
		if (param->map.map[(int)(param->act.pos.y + param->act.dir.y * move)][(int)(param->act.pos.x)] != '1')
			param->act.pos.y += param->act.dir.y * move;
	}
	if (param->act.a == 1)
	{
		if (param->map.map[(int)(param->act.pos.y)][(int)(param->act.pos.x + param->act.plane.x * move)] != '1')
			param->act.pos.x += param->act.plane.x * move;
		if (param->map.map[(int)(param->act.pos.y + param->act.plane.y * move)][(int)(param->act.pos.x)] != '1')
			param->act.pos.y += param->act.plane.y * move;
	}
}

int	movement(t_param *param)
{
	double	rot;
	double	move;

	move = 0.09;
	rot = 0.09;
	if (param->act.left == 1 || param->act.right == 1)
	{	
		param->ray.old_dir_x = param->act.dir.x;
		param->ray.old_plane_x = param->act.plane.x;
		if (param->act.left == 1)
			rot *= -1;
		param->act.dir.x = param->act.dir.x * cos(rot) - param->act.dir.y * sin(rot);
		param->act.plane.x = param->act.plane.x * cos(rot) - param->act.plane.y * sin(rot);
		param->act.dir.y = param->ray.old_dir_x * sin(rot) + param->act.dir.y * cos(rot);
		param->act.plane.y = param->ray.old_plane_x * sin(rot) + param->act.plane.y * cos(rot);
	}
	if (param->act.w == 1 || param->act.a == 1)
		key_wa(param, move);
	if (param->act.s == 1 || param->act.d == 1)
		key_sd(param, move);
	return (0);
}

void	render_sprites(t_param *param)
{
	int	count_spr;
	int	stripe;
	int	y;

	y = 0;
	count_spr = 0;
	sort_sprites(param, count_spr);
	count_spr = 0;
	while (count_spr < param->act.count_spr)
	{
		def_param_spr(param, count_spr);
		stripe = param->act.draw_start.x;
		while (stripe < param->act.draw_end.x)
		{
			draw_pixel_spr(param, stripe, y);
			stripe++;
		}
		count_spr++;
	}
}

void	render(t_param *param, int x, int y)
{
	size_t	ceil_c;
	size_t	fl_color;

	x = 0;
	while (x < param->map.scr_w)
	{
		ceil_c = create_trgb(0, param->map.ceil_c.r, param->map.ceil_c.g, param->map.ceil_c.b);
		y = 0;
		while (y <= param->map.scr_h / 2)
			my_mlx_pixel_put(param, x, y++, ceil_c);
		fl_color = create_trgb(0, param->map.floor_c.r, param->map.floor_c.g, param->map.floor_c.b);
		while (y <= param->map.scr_h - 1)
			my_mlx_pixel_put(param, x, y++, fl_color);
		x++;
	}
	x = 0;
	while (x < param->map.scr_w)
	{
		raycast(param, x);
		draw_pixel(param, x);
		x++;
	}
	render_sprites(param);
}
