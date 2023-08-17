/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:18:14 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/17 14:39:33 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_shell *shell, t_command *command)
{
	if (command->args[1])
	{
		shell_error(shell, dir_error, command->args[1], 127);
		_exit(127);
	}
	print_environment(shell->environment);
	_exit(0);
}
