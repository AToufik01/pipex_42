/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:43 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/02 19:28:25 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void    free_2d_arr(char **str)
{
    int i;
    i = 0;
    while(str[i])
        free(str[i++]);
    free(str);
}
void    inist_pipe(t_pipexb *pip,int arc, char *arv[],char *evm[])
{
    while(ft_strncmp(*evm, "PATH=", 5) != 0)
        evm++;
    *evm += 5;
    pip->env_path = ft_split (*evm, ':');
    pip->args = arv;
    pip->n = arc;
}

void    ft_here_doc(t_pipexb *pip, char *str)
{

    if (ft_strncmp(str, "here_doc",ft_strlen(str)+1) == 0)
    {
        int fd[2];
        pid_t pid;
        char *str1;
        pip->i = 3;
        pip->args[2] = ft_strjoin(pip->args[2], "\n");
        pid = fork();

        if (pid == 0)
        {
            close(fd[0]);
            while (1)
            {
                ft_putstr_fd("here_doc>", 1);
                str1 = get_next_line(0);
                if (ft_strncmp(pip->args[2], str1,ft_strlen(pip->args[2]) != 1)
                    break;
                ft_putstr_fd(str1, fd[1]);
                free(str1);
            }
        }

        else
        {
            close (fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close (fd[0]);
            wait (NULL);
        }
            // wait(NULL);
    }
    else
    {

        pip->i = 2;
        pip->infile = open();
        pip->outfile = open();
        dup2(pip->infile ,STDIN_FILENO);
        close(pip->infile);
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
        process_child_f_m(&pip, pip.i);
        pip.i++;
    }
    process_child_last(&pip);
    close(pip.outfile);
    while(wait(NULL) != -1);
    return (0);
}
 