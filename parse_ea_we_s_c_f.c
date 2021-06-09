/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ea_we_s_c_f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:54:14 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 13:56:26 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_we(char *line, t_param *param)
{
	int	i;

	if (param->map.text_path[WEST] != NULL)
		print_error("Error", "Don't pass the WE params twice");
	i = pass_space(line, 2); //start count with 2, because first 2 symbols were checked before
	valid_texture('W', &line[i], param);
}

void	parse_ea(char *line, t_param *param)
{	
	int	i;

	if (param->map.text_path[EAST] != NULL)
		print_error("Error", "Don't pass the EA params twice");
	i = pass_space(line, 2);
	valid_texture('E', &line[i], param);
}

void	parse_s(char *line, t_param *param)
{
	int	i;

	if (param->map.text_path[SPRITE] != NULL)
		print_error("Error", "Don't pass the sprite param twice");
	i = pass_space(line, 1); //start count with 1, because first symbol was checked before
	valid_texture('s', &line[i], param);
}

void	parse_c(char *line, t_param *param)
{
	int	i;

	double_check_c_param(1, param);
	check_forb_symb(line, 1, 0);
	i = pass_space(line, 1); //start count with 1, because first symbol was checked before
	valid_color(1, line, i, param);
	i = pass_digits_space(line, i);
	if (line[i] == ',')
	{
		i = pass_space(line, ++i);
		valid_color(2, line, i, param);
	}
	i = pass_digits_space(line, i);
	if (line[i] == ',')
	{
		i = pass_space(line, ++i);
		valid_color(3, line, i, param);
	}
	i = pass_digits_space(line, i);
	if (line[i] != '\0')
		print_error("Error", "Extra parameters of color: ceiling.");
	double_check_c_param(2, param);
}

void	parse_f(char *line, t_param *param)
{
	int	i;

	double_check_f_param(1, param);
	check_forb_symb(line, 1, 0);
	i = pass_space(line, 1);
	valid_color(4, line, i, param);
	i = pass_digits_space(line, i);
	if (line[i] == ',')
	{
		i = pass_space(line, ++i);
		valid_color(5, line, i, param);
	}
	i = pass_digits_space(line, i);
	if (line[i] == ',')
	{
		i = pass_space(line, ++i);
		valid_color(6, line, i, param);
	}
	i = pass_digits_space(line, i);
	if (line[i] != '\0')
		print_error("Error", "Extra parameters of color: floor.");
	double_check_f_param(2, param);
}
