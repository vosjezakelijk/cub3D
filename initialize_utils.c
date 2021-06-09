/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:09:17 by hsamatha          #+#    #+#             */
/*   Updated: 2021/05/11 18:59:16 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->ray_dir.x = 0;
	ray->ray_dir.y = 0;
	ray->side_dist.x = 0;
	ray->side_dist.y = 0;
	ray->delta_dist.x = 0;
	ray->delta_dist.y = 0;
	ray->step.x = 0;
	ray->step.y = 0;
	ray->map.x = 0;
	ray->map.y = 0;
	ray->pwd = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->line_h = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	swe_player_checker(t_param *param, char sym)
{
	if (sym == 'S')
	{
		param->act.dir.x = 0;
		param->act.dir.y = 1;
		param->act.plane.x = 0.66;
		param->act.plane.y = 0;
	}
	if (sym == 'W')
	{
		param->act.dir.x = -1;
		param->act.dir.y = 0;
		param->act.plane.x = 0;
		param->act.plane.y = 0.66;
	}
	if (sym == 'E')
	{
		param->act.dir.x = 1;
		param->act.dir.y = 0;
		param->act.plane.x = 0;
		param->act.plane.y = -0.66;
	}
}
