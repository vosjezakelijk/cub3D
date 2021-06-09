/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:55:48 by hsamatha          #+#    #+#             */
/*   Updated: 2021/05/09 18:07:45 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_final(char **cache, char **line)
{
	char		*ptr_n;

	ptr_n = ft_strchr(*cache, '\0');
	while (!ptr_n)
		break ;
	*line = ft_strdup(*cache);
	if (*line == NULL)
		return (-1);
	free(*cache);
	*cache = NULL;
	return (0);
}

static int	ft_newline(char **cache, char *ptr_n, char **line)
{
	char	*tmp;
	int		len;

	len = ft_strlen(*cache) - ft_strlen(ptr_n);
	*line = ft_substr(*cache, 0, len);
	if (!line)
		return (-1);
	tmp = ft_substr(*cache, ft_strlen(*line) + 1, ft_strlen(ptr_n));
	if (!tmp)
		return (-1);
	free(*cache);
	*cache = NULL;
	*cache = tmp;
	return (1);
}

static int	ft_line(char **cache, char **line, char *buff)
{
	char		*ptr_n;

	ptr_n = ft_strchr(*cache, '\n');
	while (!ptr_n)
		break ;
	free(buff);
	return (ft_newline(cache, ptr_n, line));
}

static void	ft_join(char **cache, char *buff)
{
	char		*tmp;

	tmp = NULL;
	tmp = ft_strjoin(*cache, buff);
	free(*cache);
	*cache = tmp;
}

int	get_next_line(int fd, char **line)
{
	static char	*cache;
	char		*buff;
	int			byte_was_read;

	buff = all_check(line, fd, &cache);
	if (ft_strchr(cache, '\n'))
		return (ft_line(&cache, line, buff));
	byte_was_read = 1;
	while (byte_was_read > 0)
	{
		byte_was_read = read(fd, buff, BUFFER_SIZE);
		buff[byte_was_read] = '\0';
		ft_join(&cache, buff);
		if (ft_strchr(cache, '\n'))
			return (ft_line(&cache, line, buff));
	}
	free(buff);
	if (ft_strchr(cache, '\0'))
		return (ft_final(&cache, line));
	if (byte_was_read == -1)
		return (-1);
	return (0);
}
