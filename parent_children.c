/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:59:27 by mcoskune          #+#    #+#             */
/*   Updated: 2024/07/15 16:21:28 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child2(t_pipex *data)
{
	dup2(data->pipefd[0], STDIN_FILENO);
	close(data->pipefd[0]);
	dup2(data->fd_out, STDOUT_FILENO);
	close(data->fd_out);
	close(data->pipefd[1]);
	if ((execve(data->cmd_path2, data->cmd2, data->envp) == -1))
		exit(9);
}

void	child1(t_pipex *data)
{
	dup2(data->fd_in, STDIN_FILENO);
	close(data->fd_in);
	dup2(data->pipefd[1], STDOUT_FILENO);
	close(data->fd_out);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	if (execve(data->cmd_path1, data->cmd1, data->envp) == -1)
		exit(15);
}

int	parent_process(t_pipex *data)
{
	pid_t	wpid;
	int		status;
	int		exit_value;
	int		i;

	close (data->fd_in);
	close (data->fd_out);
	close (data->pipefd[0]);
	close (data->pipefd[1]);
	exit_value = 77;
	i = 0;
	while (i < 2)
	{
		wpid = waitpid (data->pid[i], &status, 0);
		if (wpid == -1)
		{
			perror ("WPID ERROR");
			exit_cleanup(data);
		}
		i++;
	}
	if (WIFEXITED(status))
		exit_value = WEXITSTATUS(status);
	return (exit_value);
}
