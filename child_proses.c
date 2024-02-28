/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:49:20 by ataoufik          #+#    #+#             */
/*   Updated: 2024/02/28 20:35:38 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    process_child_f(t_pipex *pip, char *cmd1)
{
    int infile;
    char    *command;
    char    **cmd;

    infile = open(pip->args[1],O_RDONLY);
    if (infile < 0)
        exit(1);
    close(pip->fd[0]);
    dup2(infile, STDIN_FILENO);
    close(infile);
    dup2(pip->fd[1], STDOUT_FILENO);
    close(pip->fd[1]);
    command = find_path_executable(pip,cmd1);
    cmd = ft_split(pip->args[2], ' ');
    if (command == NULL)
    {
        perror("path");
        exit(1);
    }
    execve(command, cmd, NULL);
}

void    process_child_s(t_pipex *pip, char *cmd2)
{
    int outfile;
    char    *command;
    char    **cmd;

    outfile = open(pip->args[pip->n - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (outfile < 0)
        exit(1);
    close(pip->fd[1]);
    dup2(outfile, STDOUT_FILENO);
    close(outfile);
    dup2(pip->fd[0], STDIN_FILENO);
    close(pip->fd[0]);
    command = find_path_executable(pip,cmd2);
    cmd = ft_split(pip->args[3], ' ');
    if (command == NULL)
    {
        perror("path");
        exit(1);
    }
    execve(command, cmd, NULL);
}
