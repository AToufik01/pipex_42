/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:43 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/07 18:32:42 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void    inist_pipe(t_pipex *pip,int arc, char *arv[],char *evm[])
{
    if (pipe(pip->fd)== -1)
    {
        ft_putendl_fd("error",2);
        exit(1);
    }
    while(ft_strncmp(*evm, "PATH=", 5) != 0)
        evm++;
    *evm +=5;
    pip->env_path = ft_split (*evm, ':');
    pip->args = arv;
    pip->n = arc;
    pip->cmd1 = ft_split(arv[2],' ');
    pip->cmd2 = ft_split(arv[3],' ');
}

char    *find_path_executable(t_pipex *pip,char *cmd)
{
    char    *str;
    char    *path;
    int i;

    i = 0;
    str = NULL;
    path = NULL;
    // if (access(cmd, X_OK) == 0 && access(cmd, F_OK)==0)
    //     return (cmd);
    while(pip->env_path[i])
    {
        str = ft_strjoin(pip->env_path[i], "/");
        path = ft_strjoin(str, cmd);
        free(str);
        if (access(path, X_OK) == 0 && access(path, F_OK)==0)
            return (path);
        i++;
        free(path);
    }
    return NULL;
}
void    execute_process_child(t_pipex *pip)
{
    pip->pid1 = fork();
    if (pip->pid1 == -1)
        perror("error");
    if (pip->pid1 == 0)
        process_child_f(pip);
    pip->pid2 = fork();
    if (pip->pid1 == -1)
        perror("error");
    if (pip->pid2 == 0)
        process_child_s(pip);
    free_2d_arr(pip->env_path);
    free_2d_arr(pip->cmd1);
    free_2d_arr(pip->cmd2);
}

int main(int arc, char *arv[], char *evm[])
{
    t_pipex pip;
    int status;

    if (arc != 5)
        return (0);
    inist_pipe(&pip, arc, arv, evm);
    execute_process_child(&pip);
    close(pip.fd[1]);
    close(pip.fd[0]);
    waitpid(pip.pid1,&status,0);
    waitpid(pip.pid2,&status,0);
    return (0);
}
 