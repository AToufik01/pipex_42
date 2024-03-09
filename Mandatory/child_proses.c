/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:49:20 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/09 18:11:57 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	process_child_f(t_pipex *pip)
{
	int		infile;
	char	*command;

	infile = open(pip->args[1], O_RDONLY);
	if (infile < 0)
		ft_messg_error("Error opening file");
	close(pip->fd[0]);
	if (dup2(infile, STDIN_FILENO) == -1)
		ft_messg_error("Error in dup2");
	close(infile);
	if (dup2(pip->fd[1], STDOUT_FILENO) == -1)
		ft_messg_error("Error in dup2");
	close(pip->fd[1]);
	command = find_path_executable(pip, pip->cmd1[0]);
	if (command == NULL)
		ft_messg_error("Error in path");
	execve(command, pip->cmd1, NULL);
}

void	process_child_s(t_pipex *pip)
{
	int		outfile;
	char	*command;

	outfile = open(pip->args[pip->n - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile < 0)
		ft_messg_error("Error opening file");
	close(pip->fd[1]);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		ft_messg_error("Error in dup2");
	close(outfile);
	if (dup2(pip->fd[0], STDIN_FILENO) == -1)
		ft_messg_error("Error in dup2");
	close(pip->fd[0]);
	command = find_path_executable(pip, pip->cmd2[0]);
	if (command == NULL)
		ft_messg_error("Error in path");
	execve(command, pip->cmd2, NULL);
}
