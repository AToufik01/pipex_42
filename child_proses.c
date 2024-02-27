/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:49:20 by ataoufik          #+#    #+#             */
/*   Updated: 2024/02/27 19:57:18 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    process_child_f(t_pipex *pip, char *cmd1)
{
    int infile;
    char    *command;
    pip->pid1 = fork();
    if (pip->pid1 == 0)
    {
        infile = open(pip->args[2],O_RDONLY);
        if (infile < 0)
            exit(1);

        dup2(pip->fd[1], 1);
        close(pip->fd[0]);
        close(pip->fd[1]);
        command = find_path_executable(pip,cmd1);
        printf("iiiiiyiiy  %s\n",command);
        if (command == NULL)
        {
            perror("path");
            exit(1);
        }
        execve(command, pip->args, NULL);
    }
}

void    process_child_s(t_pipex *pip, char *cmd2)
{
    int outfile;
    char    *command;
    pip->pid2 = fork();
    if (pip->pid2 == 0)
    {
        outfile = open(pip->args[pip->n - 1],O_WRONLY | O_CREAT | O_TRUNC);
        if (outfile < 0)
            exit(1);

        close(pip->fd[0]);
        dup2(pip->fd[1], 1);
        command = find_path_executable(pip,cmd2);
        printf("%s\n",command);
        if (command == NULL)
        {
            perror("path");
            exit(1);
        }
        execve(command, pip->args, NULL);
        close(pip->fd[1]);
    }
}