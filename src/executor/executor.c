#include "../../include/minishell.h"

// error handling van executor werkt behalve wanneer je als promt meegeeft:
// env (dus builtin) | sdfjhsfds (unknown command)
void    executor(t_shell *shell)
{
	if (!shell->command_list || shell->command_list->count == 0)
		return ;
	if (shell->command_list->count == 1)
		handle_single_command(shell, shell->command_list->head->data);
	else
		handle_multiple_commands(shell);
	return ;
}
