/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:46:52 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/02 15:17:51 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	check_and_indxline(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*shift_buf(char *str, long n)
{
	int	i;

	i = 0;
	if (n == -1)
		n = BUFFER_SIZE;
	while (str[i + n])
	{
		str[i] = str[i + n + 1];
		i++;
	}
	while (str[i])
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

char	*read_and_set(int fd, char *buffer)
{
	char	*res;
	int		index_nl;

	index_nl = check_and_indxline(buffer);
	res = NULL;
	res = ft_strjoiin(res, buffer, index_nl + 1);
	buffer = shift_buf(buffer, index_nl);
	while (index_nl == -1 && read(fd, buffer, BUFFER_SIZE) > 0)
	{
		index_nl = check_and_indxline(buffer);
		res = ft_strjoiin(res, buffer, index_nl + 1);
		buffer = shift_buf(buffer, index_nl);
	}
	if (ft_const_strlen(res) == 0)
	{
		buffer = shift_buf(buffer, -1);
		return (free(res), NULL);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	buffer[(unsigned int)BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		shift_buf(buffer, -1);
		return (NULL);
	}
	line = read_and_set(fd, buffer);
	return (line);
}
