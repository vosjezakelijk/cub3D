/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:14:37 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 14:03:21 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *warn, char *text)
{
	printf("%s%s\n%s%s\n", RED, warn, YEL, text);
	system("afplay ./sound/bye.wav &");
	exit(errno);
	system("killall afplay");
}

void	my_mlx_pixel_put(t_param *param, int x, int y, int color)
{
	char	*dst;

	dst = param->mlx.addr + (y * param->mlx.line_len
			+ x * (param->mlx.bpp / 8));
	*(unsigned int *)dst = color;
}

char	*all_check(char **line, int fd, char **cache)
{
	char		*buff;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line || !buff || fd < 0
		 || BUFFER_SIZE < 1 || (read(fd, NULL, 0) == -1))
		print_error("Error", "Can't open this file."); //if given a directory
	if (!(*cache))
		*cache = ft_strdup("");
	return (buff);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ptr;
	size_t		string;
	int			i;

	i = 0;
	if (!s)
		return (NULL);
	string = ft_strlen((char *)s);
	if (string < start)
		len = 0;
	else if ((string - start) < len)
		len = string - start;
	ptr = (char *)malloc(len * (sizeof(char)) + 1);
	if (!(ptr))
		return (NULL);
	while (i < (int)len && s[i])
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	check_spr(t_param *param, int i, int j)
{
	if (param->map.map[i][j] == '2')
		param->act.count_spr++;
}
