/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:55:18 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 13:58:17 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(int fd, t_param *param)
{
	t_list	*map_header;
	char	*line;

	line = NULL;
	map_header = NULL;
	while ((get_next_line(fd, &line)) > 0)
	{
		ft_lstadd_back(&map_header, ft_lstnew(line)); //add what was read
		check_map_w(line, param);
	}
	ft_lstadd_back(&map_header, ft_lstnew(line)); //add final
	close(fd);
	param->map.map = make_map(&map_header, ft_lstsize(map_header), param);
}

int	pass_digits_space(char *line, int i)
{
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

void	valid_texture(char flag, char *line, t_param *param)
{
	int		len;
	char	*txtr;

	txtr = ft_strtrim(line, " \t");
	len = ft_strlen(txtr);
	if (txtr[len - 4] != '.' && txtr[len - 3] != 'p'
		 && txtr[len - 2] != 'n' && txtr[len - 1] != 'g')
		print_error("Error", "Wrong texture's format.");
	if (open(txtr, O_RDONLY) < 0)
		print_error("Error", "Invalid texture file.");
	if (flag == 'N')
		param->map.text_path[NORTH] = txtr;
	if (flag == 'S')
		param->map.text_path[SOUTH] = txtr;
	if (flag == 'W')
		param->map.text_path[WEST] = txtr;
	if (flag == 'E')
		param->map.text_path[EAST] = txtr;
	if (flag == 's')
		param->map.text_path[SPRITE] = txtr;
}

void	double_check_c_param(int flag, t_param *param)
{
	if (flag == 1)
	{
		if (param->map.ceil_c.r != -1
			 || param->map.ceil_c.g != -1
			 || param->map.ceil_c.b != -1)
			print_error("Error", "Don't pass in the ceiling param twice.");
	}
	else if (flag == 2)
	{
		if (param->map.ceil_c.r == -1
			&& param->map.ceil_c.g == -1
			&& param->map.ceil_c.b == -1)
			print_error("Error", "Missing params of color: ceiling");
	}
}

void	double_check_f_param(int f, t_param *param)
{
	if (f == 1)
	{
		if (param->map.floor_c.r != -1
			 || param->map.floor_c.g != -1
			 || param->map.floor_c.b != -1)
			print_error("Error", "Don't try to pass in the floor param twice.");
	}
	else if (f == 2)
	{
		if (param->map.floor_c.r == -1
			 && param->map.floor_c.g == -1
			 && param->map.floor_c.b == -1)
			print_error("Error", "Missing params of color: floor");
	}
}
