#include "../../include/minishell.h"

typedef void	(*t_token_type_func)(char *, size_t *, t_token_type);

/*
get_char_type checks if the given character is a meta character
or whitespace or part of a WORD.
*/

int	find_metachar(char c)
{
	const char		set[] = "|\'\"><$";
	int			i;

	i = 0;
	while (i <= 5)
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

/*
Get_token_info gets the data for the string in the token structure.
It uses a jumptable.
*/

void	get_token_info(t_shell *shell, t_token **token, char *cmd_line, size_t *i)
{
	const t_token_type_func	func[8] = {
	[0] = &tok_type_pipe,
	[1] = &tok_type_quote,
	[2] = &tok_type_quote,
	[3] = &tok_type_redir,
	[4] = &tok_type_redir,
	[5] = &tok_type_var,
	[6] = &tok_type_consec,
	[7] = &tok_type_consec,
	};
	size_t					save_i;

	if (!*token)
		return ;
	save_i = *i;
	(*token)->type = find_metachar(cmd_line[*i]);
	func[(*token)->type](cmd_line, i, (*token)->type);
	(*token)->str = ft_strndup(&(cmd_line[save_i]), *i - save_i);
	if (!(*token)->str)
	{
		free(*token);
		*token = NULL;
		shell_error(malloc_error, "lget_token_info() @ ft_strndup");
		free_shell(shell);
	}
}

/*
The lexer function takes the command line input
and returns a linked list of tokens.
*/

void	lexer(t_shell *shell)
{
	t_token	*new;
	size_t	i;

	i = 0;
	while (shell->cmd_line[i])
	{
		new_token(shell, &new);
		get_token_info(shell, &new, shell->cmd_line, &i);
		if (!new)
			return ;
		list_add_token(&(shell->lexer), new);
	}
}
