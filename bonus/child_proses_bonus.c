/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proses_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:49:20 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/10 15:31:25 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	process_child_f_m(t_pipexb *pip, int i)
{
	char	*command;

	command = NULL;
	if (pipe(pip->tub) == -1)
		ft_messg_error("error in pipe");
	pip->pid = fork();
	if (pip->pid == -1)
		ft_messg_error("Error in fork");
	if (pip->pid == 0)
	{
		close(pip->tub[0]);
		if (dup2(pip->tub[1], STDOUT_FILENO) == -1)
			ft_messg_error("Error in dup2");
		close(pip->tub[1]);
		ft_execute_command(pip, i, command);
	}
	else
	{
		close(pip->tub[1]);
		if (dup2(pip->tub[0], STDIN_FILENO) == -1)
			ft_messg_error("Error in dup2");
		close(pip->tub[0]);
	}
}

void	ft_execute_command(t_pipexb *pip, int i, char *command)
{
	char	**cmd;

	cmd = ft_split(pip->args[i], ' ');
	if (cmd == NULL)
		ft_error("Invalid argument");
	command = find_path_executable(pip, cmd[0]);
	if (command == NULL)
		ft_error("Invalid argument");
	execve(command, cmd, NULL);
	free_2d_arr(cmd);
	free(command);
}

void	process_child_last(t_pipexb *pip)
{
	char	*command;

	command = NULL;
	pip->pid = fork();
	if (pip->pid == -1)
		ft_messg_error("Error in fork");
	if (pip->pid == 0)
	{
		close(pip->tub[0]);
		dup2(pip->tub[1], STDOUT_FILENO);
		close(pip->tub[1]);
		ft_open_outfile(pip, pip->sig);
		dup2(pip->outfile, STDOUT_FILENO);
		close(pip->outfile);
		ft_execute_command(pip, pip->i, command);
	}
	else
	{
		close(pip->tub[1]);
		dup2(pip->tub[0], STDIN_FILENO);
		close(pip->tub[0]);
	}
}

char	*find_path_executable(t_pipexb *pip, char *cmd)
{
	char	*str;
	char	*path;
	int		i;

	i = 0;
	str = NULL;
	path = NULL;
	while (pip->env_path[i])
	{
		str = ft_strjoin(pip->env_path[i], "/");
		path = ft_strjoin(str, cmd);
		free(str);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		i++;
		free(path);
	}
	return (NULL);
}
