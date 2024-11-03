/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:28:32 by mcoskune          #+#    #+#             */
/*   Updated: 2024/07/17 23:31:48 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(t_pipex *data)
{
	int	exit_value;

	data->pid[0] = fork();
	if (data->pid[0] == -1)
	{
		exit_cleanup(data);
		exit(40);
	}
	if (data->pid[0] == 0)
		child1(data);
	data->pid[1] = fork();
	if (data->pid[0] == -1)
	{
		exit_cleanup(data);
		exit(40);
	}
	if (data->pid[1] == 0)
		child2(data);
	exit_value = parent_process(data);
	return (exit_value);
}

int	main(int ac, char **av, char **envp)
{
	int		exit_code;
	t_pipex	data;

	exit_code = input_validate(ac, av, envp);
	if (exit_code != 0)
		return (1);
	data = initialize_data(ac, av, envp);
	exit_code = pipex(&data);
	exit_cleanup(&data);
	return (exit_code);
}
