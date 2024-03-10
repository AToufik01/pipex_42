/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:44:54 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/10 17:37:50 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_pipexb
{
	int		n;
	int		i;
	int		sig;
	int		tub[2];
	int		infile;
	int		outfile;
	pid_t	pid;
	char	**env_path;
	char	**args;
}	t_pipexb;

char	**ft_split(char const *s, char c);
char	**ft_split_space_tab(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(const char *s);
char	*ft_strjoiin(char const *s1, char const *s2, int lens2);
int		ft_const_strlen(const char *s);
char	*get_next_line(int fd);
char	*read_and_set(int fd, char *buffer);
char	*shift_buf(char *str, long n);
int		check_and_indxline(char *str);
void	ft_here_doc(t_pipexb *pip);
void	check_here_doc(t_pipexb *pip, char *str);
void	process_child_f_m(t_pipexb *pip, int i);
void	process_child_last(t_pipexb *pip);
char	*find_path_executable_b(t_pipexb *pip, char *cmd);
void	ft_execute_command(t_pipexb *pip, int i, char *command);
void	free_2d_arr(char **str);
void	ft_messg_error(char *str);
void	ft_error(char *str);
void	ft_open_outfile(t_pipexb *pip, int i);
#endif