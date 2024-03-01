/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:51:09 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/01 17:08:15 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	ft_const_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2, int lens2)
{
	int		i;
	int		j;
	char	*p;
	int		len;
	int		lens1;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (0);
	lens1 = ft_const_strlen((char *)s1);
	if (lens2 == 0)
		lens2 = ft_const_strlen((char *)s2);
	len = lens1 + lens2;
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (free((char *)s1), NULL);
	while (s1 && s1[i])
		p[j++] = s1[i++];
	i = 0;
	while (s2 && i < lens2)
		p[j++] = s2[i++];
	p[j] = '\0';
	return (free((char *)s1), p);
}
