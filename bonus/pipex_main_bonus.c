/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:43 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/01 17:32:24 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void    inist_pipe(t_pipexb *pip,int arc, char *arv[],char *evm[])
{
    while(ft_strncmp(*evm, "PATH=", 5) != 0)
        evm++;
    *evm +=5;
    pip->env_path = ft_split (*evm, ':');
    pip->args = arv;
    pip->n = arc;
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

// void    execute_process_child(t_pipex *pip)
// {
//     pip->pid1 = fork();
//     pip->pid2 = fork();
//     if (pip->pid1 == 0)
//         process_child_f(pip, cmd1);
//     process_child_m(pip,cmd1);
//     if (pip->pid2 == 0)
//         process_child_l(pip, cmd2);
// }
void    ft_here_doc(t_pipexb *pip, char *str)
{

    if (ft_strncmp(str, "here_doc",ft_strlen(str)) == 0)
    {
        char *str;
        pip->i = 3;
        while(1)
        {
            str = get_next_line(0);
            if (ft_strncmp(pip->args[3],str,ft_strlen(pip->args[3]))== 1)
                break;
        }
        
    }
    else
    {
        pip->i = 2;  
    }
}
void    process_child_f_m(t_pipexb *pip)
{
    pip->pid = fork();
    if (pip->pid== 0)
    {
        char *command;
        // infile = open(pip->args[1],O_RDONLY);
        // if (infile < 0)
            exit(1);
        close(pip->tub[0]);
        // dup2(infile, STDIN_FILENO);
        // close(infile);
        dup2(pip->tub[1], STDOUT_FILENO);
        close(pip->tub[1]);
        command = find_path_executable(pip,pip->cmd[0]);
        if (command == NULL)
        {
            perror("path");
            exit(1);
        }
        execve(command, pip->cmd, NULL);

    
    }
    else
    {
        
    }
}
void    process_child_last(t_pipexb *pip)
{
    int outfile;
    char *command;
    pip->pid = fork();
    if (pip->pid == 0)
    {
        outfile = open(pip->args[pip->n - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (outfile < 0)
            exit(1);
        close(pip->tub[1]);
        dup2(outfile, STDOUT_FILENO);
        close(outfile);
        dup2(pip->tub[0], STDIN_FILENO);
        close(pip->tub[0]);
        command = find_path_executable(pip,pip->cmd[0]);
        if (command == NULL)
        {
            perror("path");
            exit(1);
        }
        execve(command, pip->cmd, NULL);
    }
}
int main(int arc, char *arv[], char *evm[])
{
    t_pipexb    pip;
    
    if (arc < 5)
        return (0);
    inist_pipe(&pip, arc, arv, evm);
    ft_here_doc(&pip,arv[1]);
    
    while(pip.i< arc - 2)
    {
        process_child_f_m(&pip);
        pip.i++;
    }
    process_child_last(&pip);
    
    return (0);
}
 