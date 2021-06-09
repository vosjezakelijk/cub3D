/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:15:56 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 14:09:13 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_ray_x(t_param *param) //calculate length
{
	if (param->ray.ray_dir.x == 0)
		param->ray.delta_dist.y = 0;
	else
	{
		if (param->ray.ray_dir.y == 0)
			param->ray.delta_dist.y = 1;
		else
			param->ray.delta_dist.y = fabs(1 / param->ray.ray_dir.y);
	}
	if (param->ray.ray_dir.x < 0)
	{
		param->ray.step.x = -1;
		param->ray.side_dist.x = (param->act.pos.x - param->ray.map.x)
			* param->ray.delta_dist.x;
	}
	else
	{
		param->ray.step.x = 1;
		param->ray.side_dist.x = (param->ray.map.x
				+ 1.0 - param->act.pos.x) * param->ray.delta_dist.x;
	}
}

static void	check_ray_y(t_param *param) //calculate length
{
	if (param->ray.ray_dir.y == 0)
		param->ray.delta_dist.x = 0;
	else
	{
		if (param->ray.ray_dir.x == 0)
			param->ray.delta_dist.x = 1;
		else
			param->ray.delta_dist.x = fabs(1 / param->ray.ray_dir.x);
	}
	if (param->ray.ray_dir.y < 0)
	{
		param->ray.step.y = -1;
		param->ray.side_dist.y = (param->act.pos.y - param->ray.map.y)
			* param->ray.delta_dist.y;
	}
	else
	{
		param->ray.step.y = 1;
		param->ray.side_dist.y = (param->ray.map.y
				+ 1.0 - param->act.pos.y) * param->ray.delta_dist.y;
	}
}

static void	check_sidest_end(t_param *param)
{
	if (param->ray.side == 1)
		param->ray.pwd = (param->ray.map.y - param->act.pos.y
				 + (1 - param->ray.step.y) / 2.0)
			 / param->ray.ray_dir.y;
	else if (param->ray.side == 0)
		param->ray.pwd = (param->ray.map.x - param->act.pos.x
				 + (1 - param->ray.step.x) / 2.0)
			 / param->ray.ray_dir.x;
	param->ray.line_h = (int)(param->map.scr_h / param->ray.pwd);
	param->ray.draw_start = -(param->ray.line_h)
		/ 2 + param->map.scr_h / 2;
	if (param->ray.draw_start < 0)
		param->ray.draw_start = 0;
	param->ray.draw_end = param->ray.line_h
		/ 2 + param->map.scr_h / 2;
	if (param->ray.draw_end >= param->map.scr_h)
		param->ray.draw_end = param->map.scr_h - 1;
}

static void	check_dist(t_param *param)
{
	if (param->ray.side_dist.x < param->ray.side_dist.y)
	{
		param->ray.side_dist.x += param->ray.delta_dist.x;
		param->ray.map.x += param->ray.step.x;
		param->ray.side = 0;
	}
	else
	{
		param->ray.side_dist.y += param->ray.delta_dist.y;
		param->ray.map.y += param->ray.step.y;
		param->ray.side = 1;
	}
	check_sidest_end(param);
}

void	raycast(t_param *param, int x)
{
	param->ray.camera_x = 2.0 * x / (float)param->map.scr_w - 1;
	param->ray.ray_dir.x = param->act.dir.x
		+ param->act.plane.x * param->ray.camera_x;
	param->ray.ray_dir.y = param->act.dir.y
		+ param->act.plane.y * param->ray.camera_x;
	param->ray.map.x = (int)param->act.pos.x;
	param->ray.map.y = (int)param->act.pos.y;
	check_ray_x(param);
	check_ray_y(param);
	param->ray.hit = 0;
	while (param->ray.hit == 0)
	{
		check_dist(param);
		if (param->map.map[param->ray.map.y][param->ray.map.x] == '1')
			param->ray.hit = 1;
	}
	def_texture(param);
	check_walls(param);
}
