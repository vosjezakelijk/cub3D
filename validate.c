/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:10:16 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 14:04:29 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_valid_symb(t_param *param, int i, int j, int flag)
{
	if (flag)
	{
		if (ft_strchr("02NWES", param->map.map[i][j]))
			print_error("Error", "space is not surrounded");
	}
	else
	{
		if (!(ft_strchr("012", param->map.map[i][j]))) //after replacement no othe symb allowed
			print_error("Error", "extra symbols");
	}
}

void	check_space(t_param *param, int i, int j)
{
	int	len;

	if (param->map.map[i][j] == ' ') //for each space sheck top, left, right, down
	{
		if (i != 0)
			check_valid_symb(param, (i - 1), j, 1);
		len = (int)(param->map.map_h);
		if (i != len - 1)
			check_valid_symb(param, (i + 1), j, 1);
		if (j != 0)
			check_valid_symb(param, i, (j - 1), 1);
		len = (int)(ft_strlen(param->map.map[i]));
		if (j != len - 1)
			check_valid_symb(param, i, (j + 1), 1);
		param->map.map[i][j] = '1'; //replace with 1
	}
}

void	check_player(t_param *param, int i, int j)
{
	if (ft_strchr("NSWE", param->map.map[i][j]))
	{
		if (param->map.isplayer == 1)
			print_error("Error", "Only one player is allowed.");
		if (param->map.isplayer == 0)
			param->map.isplayer = 1;
		param->act.pos.x = j + 0.5;
		param->act.pos.y = i + 0.5;
		if (param->map.map[i][j] == 'N')
		{
			param->act.dir.x = 0;
			param->act.dir.y = -1;
			param->act.plane.x = -0.66;
			param->act.plane.y = 0;
		}
		swe_player_checker(param, param->map.map[i][j]);
		param->map.map[i][j] = '0'; //read and replace with 0
	}
}

void	check_border(t_param *param, int i, int j)
{
	if (i == 0 || i == param->map.map_h - 1)
	{
		if (param->map.map[i][j] != '1')
			print_error("Error", "Open spaces on the horizontal borders.");
	}
	if (j == 0 || param->map.map[i][j + 1] == '\0')
	{
		if (param->map.map[i][j] != '1')
			print_error("Error", "Open spaces on the vertical borders");
	}
}

void	check_sprite(t_param *param, int i, int j)
{
	int	count;

	count = 0;
	i = 0;
	param->act.spr_arr = malloc(param->act.count_spr * sizeof(t_sprite));
	if (param->act.count_spr == 0)
		printf("%sWarn!\n%sNo sprites on the map.\n", GRN, BLU);
	while (param->map.map[i])
	{
		j = 0;
		while (param->map.map[i][j])
		{
			if (param->map.map[i][j] == '2')
			{
				param->act.spr_arr[count].x = j + 0.5;
				param->act.spr_arr[count].y = i + 0.5;
				count++;
			}
			j++;
		}
		i++;
	}
}
