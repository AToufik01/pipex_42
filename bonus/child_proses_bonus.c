/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proses_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:49:20 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/02 19:28:38 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void    process_child_f_m(t_pipexb *pip, int i)
{
    int fd[2];
    int file = 0;
    if (pipe(fd)== -1)
        printf("errrrororor hnaya fi process child_f_m");
    if (i == 2)
        file = open(pip->args[2], O_RDONLY);
    else if (i == 3)
        file = open(pip->args[pip->n - 1],O_WRONLY,O_CREAT,O_APPEND);
    if (file < 0)
        exit(1);
    pip->pid = fork();
    if (pip->pid == 0)
    {
        char *command;
        pip->cmd = ft_split(pip->args[i],' ');
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        command = find_path_executable(pip, pip->cmd[0]);
        if (command == NULL)
        {
            // perror("path");
            exit(1);
        }
        execve(command, pip->cmd, NULL);
        free_2d_arr(pip->cmd);
        free(command);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
    }
}

void    process_child_last(t_pipexb *pip)
{
    int outfile;
    char *command;
    pip->pid = fork();
    if (pip->pid == 0)
    {
        outfile = open(pip->args[pip->n - 1],O_WRONLY,O_CREAT,O_TRUNC);
        if (outfile < 0)
            exit(1);
        pip->cmd = ft_split(pip->args[pip->n - 1],' ');
        dup2(outfile,STDIN_FILENO);
        close(outfile);
        command = find_path_executable(pip,pip->cmd[0]);
        if (command == NULL)
        {
            // perror("path");
            exit(1);
        }
        execve(command, pip->cmd, NULL);
        free_2d_arr(pip->cmd);
        free(command);
    }
}

char    *find_path_executable(t_pipexb *pip, char *cmd)
{
    char    *str;
    char    *path;
    int i;

    i = 0;
    str = NULL;
    path = NULL;
    while(pip->env_path[i])
    {
        str = ft_strjoin(pip->env_path[i], "/");
        path = ft_strjoin(str, cmd);
        free(str);
        if (access(path, X_OK) == 0)
            return (path);
        i++;
        free(path);
    }
    return NULL;
}
