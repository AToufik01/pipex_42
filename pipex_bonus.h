/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:44:54 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/02 18:45:28 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H

#include <unistd.h>
#include <stdio.h>//
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_pipexb
{
    int tub[2];
    int n;
    int i;
    pid_t   pid;
    char    **env_path;
    char    **args;
    char    **cmd;
}   t_pipexb;


char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
int     ft_strlen(const char *s);
char	*ft_strjoiin(char const *s1, char const *s2, int lens2);
int	ft_const_strlen(const char *s);
char	*get_next_line(int fd);
char	*read_and_set(int fd, char *buffer);
char	*shift_buf(char *str, long n);
int	check_and_indxline(char *str);



void    ft_here_doc(t_pipexb *pip, char *str);
void    process_child_f_m(t_pipexb *pip, int i);

void    process_child_last(t_pipexb *pip);

char    *find_path_executable(t_pipexb *pip, char *cmd);
void    free_2d_arr(char **str);



// int ft_open_file(t_pipexb *pip, char *arg,int i);
#endif

