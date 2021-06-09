/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:01:49 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 14:00:27 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*fill_w_spaces(char *src, t_param *param)
{
	char	*dst;
	int		i;

	i = -1;
	dst = ft_calloc(param->map.map_max_w + 1, sizeof(char));
	if (dst == NULL)
		print_error("Error", "Memory error in add_space");
	while (++i < ft_strlen(src))
		dst[i] = src[i];
	while (i < param->map.map_max_w) //put spaces till the actual width
		dst[i++] = ' ';
	return (dst);
}

void	valid_color(int n, char *line, int i, t_param *param)
{
	int	c;

	c = ft_atoi(&line[i], param, 'c');
	if (c < 0 || c > 255)
		print_error("Error", "Invalid color parameters");
	if (n == 1)
		param->map.ceil_c.r = c;
	else if (n == 2)
		param->map.ceil_c.g = c;
	else if (n == 3)
		param->map.ceil_c.b = c;
	else if (n == 4)
		param->map.floor_c.r = c;
	else if (n == 5)
		param->map.floor_c.g = c;
	else if (n == 6)
		param->map.floor_c.b = c;
}

void	check_map_w(char *line, t_param *param)
{
	int	len;

	len = ft_strlen(line);
	if (len > param->map.map_max_w)
		param->map.map_max_w = len; //update if the next line has a bigger width
}

int	params_filled(t_param *param)
{
	if (param->map.scr_w != 0
		 && param->map.scr_h != 0
		 && param->map.text_path[NORTH] != 0
		 && param->map.text_path[SOUTH] != 0
		 && param->map.text_path[WEST] != 0
		 && param->map.text_path[EAST] != 0
		 && param->map.text_path[SPRITE]
		 && param->map.ceil_c.r != -1
		 && param->map.ceil_c.g != -1
		 && param->map.ceil_c.b != -1
		 && param->map.floor_c.r != -1
		 && param->map.floor_c.g != -1
		 && param->map.floor_c.b != -1)
		return (1);
	return (0);
}

char	**make_map(t_list **map_header, int size, t_param *param)
{
	char	**map;
	int		i;
	t_list	*head;

	i = -1;
	map = ft_calloc(size + 1, sizeof(char *));
	if (map == NULL)
		print_error("Error", "Memory error in make_map");
	head = *map_header;
	while (((char *)(head->content))[0] == '\0') //pass empty
		head = head->next;
	while (head)
	{
		if (((char *)(head->content))[0] != '\0') //until the end
		{
			map[++i] = fill_w_spaces(head->content, param); //here the map and all \0 edited with spaces
			param->map.map_h++;
		}
		else
			print_error("Error", "Invalid map, chars");
		head = head->next;
	}
	return (map);
}
