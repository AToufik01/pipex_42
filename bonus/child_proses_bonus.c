/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proses_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:49:20 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/08 21:35:39 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void    process_child_f_m(t_pipexb *pip, int i)
{
    if (pipe(pip->tub)== -1)
        printf("errrrororor hnaya fi process child_f_m");
    pip->pid = fork();
    /// fork --> -1
    if (pip->pid == 0)
    {
        char *command = NULL;
        close(pip->tub[0]);
        if (dup2(pip->tub[1], STDOUT_FILENO)== -1)
            printf("fffffffff\n");
        close(pip->tub[1]);
        ft_execute_command(pip, i, command);
    }
    else
    {
        close(pip->tub[1]);
        if (dup2(pip->tub[0], STDIN_FILENO)== -1)
            printf("fffffff\n");
        close(pip->tub[0]);
    }
}

void    ft_execute_command(t_pipexb *pip, int i, char *command)
{
    char    **cmd;
    cmd = ft_split(pip->args[i],' ');
    command = find_path_executable(pip, cmd[0]);
    if (command == NULL)
    {
        // perror("path");
        // exit(1);
    }
    execve(command, cmd, NULL);
    free_2d_arr(cmd);
    free(command);
    perror("command");
    exit (1);
}

void    process_child_last(t_pipexb *pip)
{
    pip->pid = fork();
    // fork --> -1
    if (pip->pid == 0)
    {
        char *command = NULL;
        close(pip->tub[0]);
        dup2(pip->tub[1],STDOUT_FILENO);
        close(pip->tub[1]);
        if (pip->sig == 1)
            pip->outfile = open(pip->args[pip->n - 1], O_CREAT|O_WRONLY|O_APPEND, 0666);
        if (pip->sig == 0)
            pip->outfile = open(pip->args[pip->n - 1], O_CREAT|O_WRONLY|O_TRUNC, 0666);
        dup2(pip->outfile, STDOUT_FILENO);
        close(pip->outfile);
        ft_execute_command(pip, pip->i, command);
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
        if (access(path,F_OK) == 0 && access(path, X_OK) == 0)
            return (path);
        i++;
        free(path);
    }
    return NULL;
}
