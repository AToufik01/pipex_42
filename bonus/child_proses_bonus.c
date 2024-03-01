/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proses_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:49:20 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/01 16:46:26 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../pipex.h"

// void    free_2d_arr(char **str)
// {
//     int i;
//     i = 0;
//     while(str[i])
//         free(str[i++]);
//     free(str);
// }
// void    process_child_f(t_pipex *pip, char *cmd1)
// {
//     int infile;
//     char    *command;

//     infile = open(pip->args[1],O_RDONLY);
//     if (infile < 0)
//         exit(1);
//     close(pip->fd[0]);
//     dup2(infile, STDIN_FILENO);
//     close(infile);
//     dup2(pip->fd[1], STDOUT_FILENO);
//     close(pip->fd[1]);
//     command = find_path_executable(pip,cmd1);
//     if (command == NULL)
//     {
//         perror("path");
//         exit(1);
//     }
//     execve(command, pip->cmd1, NULL);
// }

// void    process_child_l(t_pipex *pip, char *cmd2)
// {
//     int outfile;
//     char    *command;

//     outfile = open(pip->args[pip->n - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
//     if (outfile < 0)
//         exit(1);
//     close(pip->fd[1]);
//     dup2(outfile, STDOUT_FILENO);
//     close(outfile);
//     dup2(pip->fd[0], STDIN_FILENO);
//     close(pip->fd[0]);
//     command = find_path_executable(pip,cmd2);
//     printf("%s\n",command);
//     if (command == NULL)
//     {
//         perror("path");
//         exit(1);
//     }
//     execve(command, pip->cmd2, NULL);
// }

// void    process_child_m(t_pipex *pip, char *cmd)
// {
//     char    *command;
//     close(pip->fd[1]);
//     dup2(outfile, STDOUT_FILENO);
//     close(outfile);
//     dup2(pip->fd[0], STDIN_FILENO);
//     close(pip->fd[0]);
//     command = find_path_executable(pip,cmd2);
//     printf("%s\n",command);
//     if (command == NULL)
//     {
//         perror("path");
//         exit(1);
//     }
//     execve(command, pip->cmd2, NULL);
// }
