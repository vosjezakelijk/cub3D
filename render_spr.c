/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_spr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:16:07 by hsamatha          #+#    #+#             */
/*   Updated: 2021/05/12 13:53:17 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	division(t_pair *arr, int start, int stop)
{
	int		pivot;
	int		i;
	int		j;
	t_pair	tmp;

	pivot = start;
	i = start + 1;
	j = start + 1;
	while (j < stop + 1)
	{
		if (arr[j].dist <= arr[pivot].dist)
		{
			tmp = arr[j];
			arr[j] = arr[i];
			arr[i] = tmp;
			i++;
		}
		j++;
	}
	tmp = arr[pivot];
	arr[pivot] = arr[i - 1];
	arr[i - 1] = tmp;
	pivot = i - 1;
	return (pivot);
}

static void	start_sort(t_act *act)
{
	int	i;

	i = 0;
	if (act->pair)
		free(act->pair);
	act->pair = malloc(act->count_spr * sizeof(t_pair));
	while (i < act->count_spr)
	{
		act->pair[i].dist = act->sp_dist[i];
		act->pair[i].order = act->sp_order[i];
		i++;
	}
	sort_next(act->pair, 0, act->count_spr - 1);
}

void	sort_sprites(t_param *param, int count_spr)
{
	int	i;

	i = 0;
	while (count_spr < param->act.count_spr)
	{
		param->act.sp_order[count_spr] = count_spr;
		param->act.sp_dist[count_spr]
			 = ((param->act.pos.x - param->act.spr_arr[count_spr].x)
				* (param->act.pos.x - param->act.spr_arr[count_spr].x)
				+ (param->act.pos.y - param->act.spr_arr[count_spr].y)
				* (param->act.pos.y - param->act.spr_arr[count_spr].y));
		count_spr++;
	}
	start_sort(&(param->act));
	while (i < param->act.count_spr)
	{
		param->act.sp_dist[i]
			 = param->act.pair[param->act.count_spr - i - 1].dist;
		param->act.sp_order[i]
			 = param->act.pair[param->act.count_spr - i - 1].order;
		i++;
	}
}

static void	def_srt_end_spr(t_param *param)
{
	param->act.draw_start.y = -param->act.sp_height
		/ 2 + param->map.scr_h / 2;
	if (param->act.draw_start.y < 0)
		param->act.draw_start.y = 0;
	param->act.draw_end.y = param->act.sp_height
		/ 2 + param->map.scr_h / 2;
	if (param->act.draw_end.y >= param->map.scr_h)
		param->act.draw_end.y = param->map.scr_h - 1;
	param->act.sp_width = abs((int)(param->map.scr_h
				/ (param->act.transf.y)));
	param->act.draw_start.x = -param->act.sp_width
		/ 2 + param->act.sp_screen_x;
	if (param->act.draw_start.x < 0)
		param->act.draw_start.x = 0;
	param->act.draw_end.x = param->act.sp_width
		/ 2 + param->act.sp_screen_x;
	if (param->act.draw_end.x >= param->map.scr_w)
		param->act.draw_end.x = param->map.scr_w - 1;
}

void	def_param_spr(t_param *param, int count_spr)
{
	param->act.cur_sp.x = param->act.spr_arr
	[param->act.sp_order[count_spr]].x - param->act.pos.x;
	param->act.cur_sp.y = param->act.spr_arr
	[param->act.sp_order[count_spr]].y - param->act.pos.y;
	param->act.inv_det = 1.0 / (param->act.plane.x
			* param->act.dir.y - param->act.dir.x * param->act.plane.y);
	param->act.transf.x = param->act.inv_det * (param->act.dir.y
			 * param->act.cur_sp.x - param->act.dir.x
			 * param->act.cur_sp.y);
	param->act.transf.y = param->act.inv_det * (-param->act.plane.y
			* param->act.cur_sp.x + param->act.plane.x
			 * param->act.cur_sp.y);
	param->act.sp_screen_x = (int)((param->map.scr_w / 2.0)
			* (1 + param->act.transf.x / param->act.transf.y));
	param->act.sp_height = abs((int)(param->map.scr_h
				/ (param->act.transf.y)));
	def_srt_end_spr(param);
}
