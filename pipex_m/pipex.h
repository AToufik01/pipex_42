/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:05:26 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/02 15:20:05 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct s_pipex
{
    int fd[2];
    pid_t   pid1;
    pid_t   pid2;
    int     n;
    char    **env_path;
    char    **args;
    char    **cmd1;
    char    **cmd2;
}   t_pipex;



char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
int     ft_strlen(const char *s);
void    free_2d_arr(char **str);
void	*ft_calloc(size_t count, size_t size);
void    inist_pipe(t_pipex *pip,int arc, char *arv[],char *evm[]);
void    execute_process_child(t_pipex *pip);
void    process_child_f(t_pipex *pip);
char    *find_path_executable(t_pipex *pip,char *cmd);
void    process_child_s(t_pipex *pip);

#endif