/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:12:30 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/09 13:28:46 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!(*lst))
		(*lst) = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!(new))
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*tmp;

	if (lst == NULL)
		return (0);
	len = 1;
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&(s[i]));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&(s[i]));
	return (0);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	len = 0;
	while (s1[i++])
		len = i;
	p = (char *)malloc((len + 1));
	if (!(p))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
