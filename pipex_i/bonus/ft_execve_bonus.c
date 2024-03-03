/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:03:01 by mohimi            #+#    #+#             */
/*   Updated: 2024/02/19 13:33:35 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_execve(char **cmd, char **envp, t_bpipex *bpipe)
{
	bpipe->split_cmd = ft_split(cmd[0], ' ');
	bpipe->chec = ft_get_path(envp);
	if (!bpipe->split_cmd[0] || !bpipe->chec)
		ft_error_message("command not found!");
	bpipe->result = check_cmd(bpipe->chec, bpipe->split_cmd);
	if (bpipe->result)
	{
		if (execve(bpipe->result, bpipe->split_cmd, envp) == -1)
			ft_error_message("error message from execve!");
	}
	else
		ft_error_message("error from access!");
}

int	ft_open_files(char *av, int i)
{
	int	fd;

	fd = -1;
	if (i == 0)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 1)
		fd = open(av, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 2)
		fd = open(av, O_RDONLY, 0644);
	else if (i == -1)
		ft_error_message("Error from open!");
	return (fd);
}