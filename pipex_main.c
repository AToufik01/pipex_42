/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:43 by ataoufik          #+#    #+#             */
/*   Updated: 2024/02/27 19:58:58 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    inist_pipe(t_pipex *pip,int arc, char *arv[],char *evm[])
{
    if (pipe(pip->fd)== -1)
    {
        perror("pipe");
        exit(1);
    }
    while(ft_strncmp(*evm, "PATH=", 5) != 0)
        evm++;
    *evm +=5;
    pip->env_path = ft_split (*evm, ':');
    pip->args = arv;
    pip->n = arc;
}

char    *find_path_executable(t_pipex *pip, char *cmd)
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


int main(int arc, char *arv[], char *evm[])
{
    t_pipex pip;
    int status;
    int i;
    i = 0;

    if (arc != 5)
        return (0);
    inist_pipe(&pip, arc, arv, evm);

    process_child_f(&pip,arv[2]);
    process_child_s(&pip,arv[3]);
    close(pip.fd[0]);
    close(pip.fd[1]);
    waitpid(pip.pid1,&status,0);
    waitpid(pip.pid2,&status,0);
    return (0);
}
 