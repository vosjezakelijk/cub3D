/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:49:13 by hsamatha          #+#    #+#             */
/*   Updated: 2021/05/12 13:09:36 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	ft_check(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	while (src[i])
		i++;
	if (size == 0)
		return (i);
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*make_res(unsigned int	size)
{
	char	*result;

	result = malloc(sizeof(char) * size);
	if (!result)
		return (NULL);
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	unsigned int	size;
	char			*first;
	char			*last;
	char			*result;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_check(s1[i], set))
		i++;
	first = (char *)(&s1[i]);
	i = ft_strlen(first) - 1;
	if (i != -1)
		while (i >= 0 && ft_check(s1[i], set))
			i--;
	last = (char *)&s1[i];
	if (!*s1 || first == last)
		size = 2;
	else
		size = last - first + 2;
	result = make_res(size);
	ft_strlcpy(result, first, size);
	return (result);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*dest;
	int		i;

	if (!(s1) || !(s2))
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(len * (sizeof(char)) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (*s1)
	{
		dest[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		dest[i] = *s2++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
