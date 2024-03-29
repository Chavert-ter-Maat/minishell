/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 13:30:09 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 17:59:56 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef void	(*t_find_end_token)(char *, size_t *, int);

int	get_token_type(char c)
{
	const char	set[] = "x|\'\"><$";
	int			i;

	i = 1;
	while (i <= 6)
	{
		if (set[i] == c)
			return (i);
		i++;
	}
	if (c == ' ' || c == '\t' || c == '\n')
		return (i);
	i++;
	return (i);
}

static void	get_token_info(t_shell *shell, t_token *token,
		char *cmd_line, size_t *i)
{
	const t_find_end_token	func[9] = {
	[0] = NULL,
	[1] = &find_end_pipe,
	[2] = &find_end_quote,
	[3] = &find_end_quote,
	[4] = &find_end_redir,
	[5] = &find_end_redir,
	[6] = &find_end_var,
	[7] = &find_end_consec,
	[8] = &find_end_consec,
	};
	size_t					save_i;

	save_i = *i;
	token->type = get_token_type(cmd_line[*i]);
	func[token->type](cmd_line, i, token->type);
	token->str = ft_strndup(&(cmd_line[save_i]), *i - save_i);
	if (!token->str)
		shell_error(shell, malloc_error, "get_token_info()", 1);
}

void	lexer(t_shell *shell)
{
	size_t	i;
	t_token	*new;

	shell->token_list = list_create(shell, sizeof(t_token),
			free_token, comp_token);
	i = 0;
	while (shell->token_list && shell->cmd_line[i])
	{
		new = ft_calloc(1, sizeof(t_token));
		if (!new)
			return (shell_error(shell, malloc_error, "lexer", 1));
		get_token_info(shell, new, shell->cmd_line, &i);
		if (list_add_new_node(shell, shell->token_list, new))
			free(new);
		else
			free_token(new);
	}
}
