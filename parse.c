/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:18:47 by mcoskune          #+#    #+#             */
/*   Updated: 2024/07/17 23:25:43 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_correct_path(char *cmd_x, char **paths)
{
	int		i;
	char	*test_path;
	char	*full_path;

	test_path = NULL;
	full_path = NULL;
	i = 0;
	while (paths[i])
	{
		test_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(test_path, cmd_x);
		free (test_path);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			return (full_path);
		}
		free (full_path);
		i++;
	}
	return (NULL);
}

static char	*env_path_string(char **envp)
{
	int		i;
	char	*path;

	path = NULL;
	i = 0;
	while (envp[i] != NULL && envp[i][0] != '\0')
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
		{
			path = ft_substr(path, 5, ft_strlen(path));
			break ;
		}
		i++;
	}
	return (path);
}

static void	get_cmd_paths(t_pipex *init)
{
	char	*envp_path_str;
	char	**paths;

	envp_path_str = env_path_string(init->envp);
	paths = ft_split(envp_path_str, ':');
	free(envp_path_str);
	if (paths == NULL)
	{
		exit_cleanup(init);
		exit (6);
	}
	init->cmd_path1 = find_correct_path(init->cmd1[0], paths);
	init->cmd_path2 = find_correct_path(init->cmd2[0], paths);
	free_str(NULL, paths);
}

static void	get_cmds(t_pipex *init)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (i == 0 && init->av[2][0] != '\0')
			init->cmd1 = ft_split(init->av[i + 2], ' ');
		else if (i == 1 && init->av[3][0] != '\0')
			init->cmd2 = ft_split(init->av[i + 2], ' ');
		i++;
	}
	if (init->cmd1 == NULL || init->cmd2 == NULL)
	{
		perror("Command not found, no more gotchas for you!");
		exit_cleanup(init);
		exit(100);
	}
}

void	fill_cmd_stuff(t_pipex *init)
{
	get_cmds(init);
	get_cmd_paths(init);
	if (init->cmd_path1 == NULL || init->cmd_path2 == NULL)
	{
		ft_putstr_fd("path me bananas", 2);
		exit_cleanup(init);
		exit (6);
	}
}
