/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:30:13 by mohimi            #+#    #+#             */
/*   Updated: 2024/02/19 11:01:26 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_middle_cmds(char *command, char **envp, t_bpipex *bpipe)
{
	if (pipe(bpipe->fd) == -1)
		ft_error_message("Error from pipe");
	bpipe->pid = fork();
	if (bpipe->pid == 0)
	{
		close(bpipe->fd[0]);
		dup2(bpipe->fd[1], STDOUT_FILENO);
		close(bpipe->fd[1]);
		ft_execve(&command, envp, bpipe);
	}
	else
	{
		close(bpipe->fd[1]);
		dup2(bpipe->fd[0], STDIN_FILENO);
		close(bpipe->fd[0]);
	}
}

void	last_cmd(int ac, char **av, char **env, t_bpipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		ft_error_message("Error from fork!");
	if (pipex->pid == 0)
	{
		close(pipex->fd[0]);
		dup2(pipex->fd[1], STDOUT_FILENO);
		close (pipex->fd[1]);
		dup2(pipex->fileout, STDOUT_FILENO);
		ft_execve(&av[ac - 2], env, pipex);
	}
	else
	{
		close(pipex->fd[1]);
		dup2(pipex->fd[0], STDIN_FILENO);
		close(pipex->fd[0]);
	}
}

void	ft_here_doc(t_bpipex *pipex)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			ft_putstr_fd("here_doc>", 1);
			str1 = get_next_line(0);
			if (ft_strncmp(pip->args[2], str1,ft_strlen(pip->args[2]) != 1)
				break;
			ft_putstr_fd(str1, fd[1]);
			free(str1);
		}
	}

	else
	{
		close (fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close (fd[0]);
		wait (NULL);
	}
}

