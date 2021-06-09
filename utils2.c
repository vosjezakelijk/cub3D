/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:12:25 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 14:05:58 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *argv)
{
	int	l;

	l = 0;
	while (argv[l] != '\0')
		l++;
	return (l);
}

int	ft_atoi(const char *str, t_param *param, char ch)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
		i++;
	}
	if (i > 4) // if discgange is biggen then 4 -- not valid, need to adopt
	{
		if (ch == 'w')
			param->map.w_atoi = 1;
		if (ch == 'h')
			param->map.h_atoi = 1;
		if (ch == 'c')
			print_error("Error", "Invalid color parameter.");
	}
	return (result);
}

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*s_str;
	size_t			i;

	s_str = s;
	if (n == 0)
		return (s);
	i = 0;
	while (i < n)
	{
		s_str[i] = '\0';
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	result;

	result = count * size;
	ptr = (char *)malloc(result);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, result);
	return (ptr);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
