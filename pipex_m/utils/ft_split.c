/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:14:05 by ataoufik          #+#    #+#             */
/*   Updated: 2024/02/29 15:38:22 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	ft_cont_word(const char *str, char c)
{
	int	cont;

	cont = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			cont++;
		while (*str != c && *str)
			str++;
	}
	return (cont);
}

static char	**ft_strspil(char **str, char const *s, char c, int count)
{
	int	i;
	int	j;

	i = 0;
	while (count > i)
	{
		j = 0;
		while (s[j] != c && s[j])
			j++;
		str[i] = ft_substr(s, 0, j);
		if (!str[i])
		{
			while (i--)
				free(str[i]);
			free(str);
			return (0);
		}
		while (s[j] == c && s[j])
			j++;
		s = s + j;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		words;

	if (!s)
		return (NULL);
	words = ft_cont_word(s, c);
	str = (char **)malloc((words + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (*s == c && *s)
		s++;
	str = ft_strspil(str, s, c, words);
	return (str);
}
