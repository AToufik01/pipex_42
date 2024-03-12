/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:10:32 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/10 21:48:06 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	ft_open_outfile(t_pipexb *pip, int i)
{
	if (i == 1)
		pip->outfile = open(pip->args[pip->n - 1],
				O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (i == 0)
		pip->outfile = open(pip->args[pip->n - 1],
				O_CREAT | O_WRONLY | O_TRUNC, 0666);
}

void	free_2d_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	ft_messg_error(char *str)
{
	perror(str);
	exit(1);
}

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}
