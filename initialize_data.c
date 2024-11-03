/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:50:21 by mcoskune          #+#    #+#             */
/*   Updated: 2024/07/17 22:58:55 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	fd_in_out(t_pipex *init)
{
	init->fd_in = open(init->av[1], O_RDONLY, 644);
	if (init->fd_in == -1)
	{
		perror("Your infile sucks");
		exit_cleanup(init);
		exit(20);
	}
	init->fd_out = open(init->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (init->fd_out == -1)
	{
		perror("Open Failed - OUTFILE");
		exit_cleanup(init);
		exit(20);
	}
}

void	redirect_io(int input, int output, t_pipex *data)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		exit_cleanup(data);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		exit_cleanup(data);
	}
}

static void	create_pipe(t_pipex *init)
{
	if (pipe(init->pipefd) == -1)
	{
		perror("Pipe is lost in abyss");
		exit_cleanup(init);
	}
}

t_pipex	initialize_data(int ac, char **av, char **envp)
{
	t_pipex	init;

	init.ac = ac;
	init.av = av;
	init.envp = envp;
	init.fd_in = -1;
	init.fd_out = -1;
	init.pipefd[0] = -1;
	init.pipefd[1] = -1;
	init.pid[0] = -1;
	init.pid[1] = -1;
	init.cmd1 = NULL;
	init.cmd2 = NULL;
	init.cmd_path1 = NULL;
	init.cmd_path2 = NULL;
	fill_cmd_stuff(&init);
	create_pipe(&init);
	fd_in_out(&init);
	return (init);
}
