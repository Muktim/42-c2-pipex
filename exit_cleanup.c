/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:05:50 by mcoskune          #+#    #+#             */
/*   Updated: 2024/07/15 19:46:45 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str(char *str, char **dstr)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	i = 0;
	if (dstr != NULL)
	{
		while (dstr[i])
		{
			free(dstr[i]);
			i++;
		}
		free(dstr);
		dstr = NULL;
	}
}

static void	close_pipe_fds(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (data->pipefd[i] != -1)
			close (data->pipefd[i]);
		i++;
	}
}

void	close_fd(t_pipex *data)
{
	if (data->fd_in != -1)
		close (data->fd_in);
	if (data->fd_out != -1)
		close (data->fd_out);
	close_pipe_fds(data);
}

void	exit_cleanup(t_pipex *data)
{
	if (data)
	{
		close_fd(data);
		if (data->cmd1 != NULL || data->cmd_path1 != NULL)
			free_str(data->cmd_path1, data->cmd1);
		if (data->cmd2 != NULL || data->cmd_path2 != NULL)
			free_str(data->cmd_path2, data->cmd2);
	}
}
