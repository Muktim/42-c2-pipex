/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:28:28 by mcoskune          #+#    #+#             */
/*   Updated: 2024/07/15 16:22:46 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include "./LIBFT/libft.h"

typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**envp;
	int		fd_in;
	int		fd_out;
	int		pipefd[2];
	int		pid[2];
	char	**cmd1;
	char	**cmd2;
	char	*cmd_path1;
	char	*cmd_path2;
}	t_pipex;

/*------- INITIAL CHECK -------*/
int		input_validate(int ac, char **av, char **envp);

/*------- INITIALIZE -------*/
t_pipex	initialize_data(int ac, char **av, char **envp);
void	fill_cmd_stuff(t_pipex *init);

/*------- CLEANUP -------*/
void	free_str(char *str, char **dstr);
void	exit_cleanup(t_pipex *data);
void	close_fd(t_pipex *data);

/*------- PIPES_FOR_DAYS -------*/
int		parent_process(t_pipex *data);
void	child2(t_pipex *data);
void	child1(t_pipex *data);
void	redirect_io(int input, int output, t_pipex *data);

#endif