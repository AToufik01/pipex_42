/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:44:54 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/01 17:23:22 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H
#include <unistd.h>
#include <fcntl.h>
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




#endif

