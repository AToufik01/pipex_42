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
    if (pipe(pip->tub)== -1)
        printf("errrrororor hnaya fi process child_f_m");
    pip->pid = fork();
    if (pip->pid == 0)
    {
        char *command;
        pip->cmd = ft_split(pip->args[i],' ');
        close(pip->tub[0]);
        dup2(pip->tub[1], STDOUT_FILENO);
        close(pip->tub[1]);
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
        close(pip->tub[1]);
        dup2(pip->tub[0], STDIN_FILENO);
        close(pip->tub[0]);
    }
}

void    process_child_last(t_pipexb *pip)
{
    pip->pid = fork();
    if (pip->pid == 0)
    {
        char *command;
        pip->cmd = ft_split(pip->args[pip->n - 1],' ');
        close(pip->tub[0]);
        dup2(pip->tub[1],STDOUT_FILENO);
        close(pip->tub[1]);
        dup2(pip->outfile, STDOUT_FILENO);
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
    else
    {
        close(pip->tub[1]);
        dup2(pip->tub[0],STDIN_FILENO);
        close(pip->tub[0]);
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
