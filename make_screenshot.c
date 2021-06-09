/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 21:09:24 by hsamatha          #+#    #+#             */
/*   Updated: 2021/05/11 18:54:55 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_in_char(unsigned char *start, int value)
{
	unsigned char	i;

	i = (unsigned char)(value);
	start[0] = value;
	start[1] = value >> 8;
	start[2] = value >> 16;
	start[3] = value >> 24;
}

static void	header(int fd, t_param *param)
{
	unsigned char	header[54];
	int				file_size;

	ft_bzero(header, 54);
	file_size = 54 + ((4 * param->map.scr_w) * param->map.scr_h);
	header[0] = 'B';
	header[1] = 'M';
	set_in_char(header + 2, file_size);
	header[10] = 54;
	header[14] = 40;
	set_in_char(header + 18, param->map.scr_w);
	set_in_char(header + 22, param->map.scr_h);
	header[26] = 1;
	header[28] = 32;
	write(fd, header, 54);
}

void	make_screenshot(t_param *param, char *name)
{
	int	fd;
	int	x;
	int	y;
	int	color;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		print_error("Error", "Problems with a screenshot.");
	header(fd, param);
	x = param->map.scr_h;
	while (--x >= 0)
	{
		y = -1;
		while (++y < param->map.scr_w)
		{
			color = *(int *)(param->mlx.addr
					 + (x * param->mlx.line_len
						  + y * (param->mlx.bpp / 8)));
			write(fd, &color, 4);
		}
	}	
	printf("%sSucces!\n%sScreenshot in the directory.\n", GRN, BLU);
	exit(0);
}

int	pass_space(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
