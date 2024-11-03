/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:16:07 by mcoskune          #+#    #+#             */
/*   Updated: 2024/07/15 19:48:25 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	input_validate(int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		ft_putstr_fd("Error - Problematic argument count", 2);
		return (1);
	}
	if (!av || !*av)
	{
		ft_putstr_fd("Error - empty av", 2);
		return (1);
	}
	if (!envp || !*envp)
	{
		ft_putstr_fd("Error - envp could not be found", 2);
		return (1);
	}
	return (0);
}
