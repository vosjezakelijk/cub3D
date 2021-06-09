/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_res_no_so.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:52:50 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 13:57:42 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_res(char ch, char *line, int i, t_param *param)
{
	int	real_w_screen;
	int	real_h_screen;
	int	k;

	k = ft_atoi(&line[i], param, ch); //modified atoi!
	mlx_get_screen_size(param->mlx.ptr, &real_w_screen, &real_h_screen);
	if (ch == 'w')
	{
		param->map.scr_w = k;
		if ((param->map.scr_w > real_w_screen) && param->map.w_atoi) //adopr the screensize if markers are on
			param->map.scr_w = real_w_screen;
	}
	else if (ch == 'h')
	{
		param->map.scr_h = k;
		if ((param->map.scr_h > real_h_screen) && param->map.h_atoi)
			param->map.scr_h = real_h_screen;
	}
	if (k == 0)
		print_error("Error", "Null param of resolution.");
}

void	check_forb_symb(char *line, int i, int flag)
{
	while (line[i])
	{
		if (flag)
		{
			if (!(ft_strchr(" 0123456789\t", line[i]))) //for resolution check
				print_error("Error", "Kek! Forbidden symbols in res.");
		}
		else
		{
			if (!(ft_strchr(" ,0123456789\t", line[i]))) //for color check
				print_error("Error", "Kek! Forbidden symbols in rbg.");
		}
		i++;
	}
}

void	parse_res(char *line, t_param *param)
{
	int	i;

	if (param->map.scr_w != 0 && param->map.scr_h != 0)
		print_error("Error", "Don't pass the res param twice");
	check_forb_symb(line, 1, 1);
	i = pass_space(line, 1);
	process_res('w', line, i, param);
	i = pass_digits_space(line, i);
	process_res('h', line, i, param);
	i = pass_digits_space(line, i);
	if (line[i] != '\0')
		print_error("Error", "Extra resolution parameters.");
}

void	parse_no(char *line, t_param *param)
{
	int	i;

	if (param->map.text_path[NORTH] != NULL)
		print_error("Error", "Don't pass the NO params twice");
	i = pass_space(line, 2);
	valid_texture('N', &line[i], param);
}

void	parse_so(char *line, t_param *param)
{	
	int	i;

	if (param->map.text_path[SOUTH] != NULL)
		print_error("Error", "Don't pass the SO params twice");
	i = pass_space(line, 2);
	valid_texture('S', &line[i], param);
}
