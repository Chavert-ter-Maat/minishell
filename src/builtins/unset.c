/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:17:18 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 18:15:29 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(t_shell *shell, t_command *command)
{
	t_node	*target;
	size_t	index;
	t_var	*var;

	if (!command->args[1])
		return ;
	index = 1;
	while (command->args[index])
	{
		target = list_get_node(shell->environment, command->args[index++]);
		if (target)
		{
			var = (t_var *) target->data;
			list_remove_node(shell->environment, var->name);
		}
	}
	shell->status = 0;
}
