/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:06:43 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/11 18:13:15 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	inist_pipe(t_pipexb *pip, int arc, char *arv[], char *evm[])
{
	char	*default_path;

	pip->args = arv;
	pip->n = arc;
	if (!evm || !*evm)
	{
		default_path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:";
		pip->env_path = ft_split (default_path, ':');
		if (!pip->env_path)
			ft_error("Invalid argument");
		return ;
	}
	while (evm && *evm && ft_strncmp(*evm, "PATH=", 5) != 0)
		evm++;
	if (*evm == NULL)
		ft_error("Path not found");
	*evm += 5;
	pip->env_path = ft_split (*evm, ':');
	if (!pip->env_path)
		ft_error("Invalid argument");
}

void	ft_here_doc(t_pipexb *pip)
{
	int		fds[2];
	char	*str;

	if (pipe(fds) == -1)
		ft_messg_error("error in pipe");
	pip->args[2] = ft_strjoin(pip->args[2], "\n");
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		str = get_next_line(0);
		if (str == NULL
			|| (ft_strncmp(pip->args[2], str, ft_strlen(pip->args[2])) != 1))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fds[1]);
		free(str);
	}
	close (fds[1]);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		ft_messg_error("Error in dup2");
	close (fds[0]);
}

void	check_here_doc(t_pipexb *pip, char *str)
{
	if (ft_strncmp(str, "here_doc", ft_strlen(str) + 1) == 0)
	{
		if (pip->n < 6)
			ft_error("Error : incorrect number of arguments");
		pip->i = 3;
		pip->sig = 1;
		ft_here_doc(pip);
	}
	else
	{
		if (pip->n < 5)
			ft_error("Error : incorrect number of arguments");
		pip->i = 2;
		pip->sig = 0;
		pip->infile = open(pip->args[1], O_RDONLY);
		if (dup2(pip->infile, STDIN_FILENO) == -1)
			ft_messg_error("Error in dup2");
		close(pip->infile);
	}
}

int	main(int arc, char *arv[], char *evm[])
{
	t_pipexb	pip;

	inist_pipe(&pip, arc, arv, evm);
	check_here_doc(&pip, arv[1]);
	while (pip.i < arc - 2)
	{
		process_child_f_m(&pip, pip.i);
		pip.i++;
	}
	process_child_last(&pip);
	free_2d_arr(pip.env_path);
	while (wait(NULL) != -1)
		;
	return (0);
}
