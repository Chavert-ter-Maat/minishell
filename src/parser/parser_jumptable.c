/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_jumptable.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 13:50:31 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/28 14:18:11 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*skip_token(t_shell *shell, t_node *node, t_command *new)
{
	(void) shell;
	if (!new)
		return (NULL);
	else
		return (node->next);
}

static t_redir_type	get_redir_type(t_shell *shell, t_node *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (token->str[0] == '>')
	{
		if (token->str[1] == '>')
			return (APPEND);
		if (token->str[1] == '\0')
			return (OUT);
	}
	if (token->str[0] == '<')
	{
		if (token->str[1] == '<')
			return (HEREDOC);
		if (token->str[1] == '\0')
			return (IN);
	}
	shell_error(shell, syntax_error, (const char *)token->str, 1);
	return (REDIR);
}

t_node	*add_cmd_redir(t_shell *shell, t_node *node, t_command *new_cmd)
{
	t_redir	*new_redir;
	t_token	*token;

	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return (shell_error(shell, malloc_error, "add_cmd_redir", 1), NULL);
	new_redir->type = get_redir_type(shell, node);
	node = node->next;
	skip_space(&node);
	if (!node)
		return (free(new_redir), shell_error(shell, syntax_error,
				"newline", 1), NULL);
	token = (t_token *) node->data;
	if (token->type != WORD)
		return (free(new_redir), shell_error(shell, syntax_error,
				token->str, 1), NULL);
	new_redir->file = ft_strdup(token->str);
	if (!(new_redir->file))
		return (free_redir(new_redir), shell_error(shell, malloc_error,
				"add_cmd_redir() @ ft_strdup", 1), NULL);
	if (list_add_new_node(shell, new_cmd->redir_list, new_redir))
		free(new_redir);
	else
		free_redir(new_redir);
	return (node->next);
}

t_node	*add_cmd_arg(t_shell *shell, t_node *node, t_command *new)
{
	char	*arg;
	t_token	*token;

	token = (t_token *)node->data;
	arg = ft_strdup(token->str);
	if (!arg)
		return (shell_error(shell, malloc_error,
				"add_cmd_arg() @ ft_strdup", 1), node);
	if (!list_add_new_node(shell, new->arg_list, &arg))
		free(arg);
	return (node->next);
}
