#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <errno.h>
# include <sys/errno.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"

// defines
# define WRITE_END	1
# define READ_END	0
# define SUCCESS	0
# define FOUND		1
# define NOT_FOUND	0
# define FAILED		-1
# define ERROR		-1
# define TRUE		1
# define FALSE		0
 
// enums
typedef enum e_token_type {

	TOKEN = 0,
	PIPE,
	QUOTE,
	DQUOTE,
	GREAT,
	LESS,
	VAR,
	SPACE,
	WORD
}	t_token_type;

typedef enum e_redir_type 
{
	REDIR = 0,
	IN,
	OUT,
	HEREDOC,
	APPEND,
}	t_redir_type;

// functions

typedef	void(*func_ptr_free)(void *);
typedef int(*func_ptr_comp)(void *, void *);


//structs
typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	size_t			data_size;
	int				count;
	t_node			*head;
	t_node			*tail;
	func_ptr_free	ft_free;
	func_ptr_comp	ft_comp;
} t_list;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
}	t_token;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
}	t_redir;

typedef struct s_command
{
	char	**args;
	t_list	*arg_list;
	t_list	*redir_list;
}	t_command;

typedef struct s_executor
{	
  	int 		temp_stdin;
	int 		temp_stdout;
	char		*cmd_line;
	int			argc;
	char		**argv;
	char		**envp;
	char		*infile;
	char		*outfile;
	int			pipe_infile[2];
}	t_executor;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				is_set;
	struct	s_env	*next;
}	t_env;

typedef struct s_shell
{
	int					return_value;
	char				*cmd_line;
	struct s_builtins	*builtins;
	t_list				*command_list;
	t_env				*env_list;
  	t_executor	 		*executor;
	t_list				*token_list;
	char				**envp;
}	t_shell;

typedef struct s_builtins
{
	const char	*type_builtin;
	void		(*function)(t_shell *shell, char **arguments);
}	t_builtins;

// lexer
void	lexer(t_shell *shell);
int		get_token_type(char c);
void	find_end_pipe(char *cmd_line, size_t *i, int type);
void	find_end_quote(char *cmd_line, size_t *i, int type);
void	find_end_redir(char *cmd_line, size_t *i, int type);
void	find_end_var(char *cmd_line, size_t *i, int type);
void	find_end_consec(char *cmd_line, size_t *i, int type);

//expander
void	expander(t_shell *shell);
char 	*get_var_value(t_shell *shell, char *var);
void	list_cat_words(t_shell *shell, t_list *list);
void	list_add_new_word(t_shell *shell, t_list *list, char *str, size_t *i);
void	list_add_token_copy(t_shell *shell, t_list *list, t_token *token);

//parser
void	parser(t_shell *shell);
void	skip_space(t_node **node);
t_node	*add_cmd_arg(t_shell *shell, t_node *node, t_command *new);
t_node	*add_cmd_redir(t_shell *shell, t_node *node, t_command *new_cmd);
t_node	*skip_token(t_shell *shell, t_node *node, t_command *new);
char	**arg_list_to_array(t_command *command);

// utils
void	free_shell(t_shell *shell);
void	shell_error(t_shell *shell, void (*func)(const char *), const char *str, int ret);
void	print_error(const char *str);
void	malloc_error(const char *str);
void	syntax_error(const char *str);

//test functions
void	print_command_table(t_shell *shell);
void	print_token_list(t_shell *shell);

// executor
void    executor(t_shell *shell);
void	run_command(t_shell *shell, char **argv);
void	handle_multiple_commands(t_shell *shell);
void	handle_single_command(t_shell *shell);
int		ft_here_doc(char *delimiter, int fd_write_end);

// void	input_handling(t_shell *shell, int argc, char **argv, char **envp);
void	print_status_waidpid(pid_t pid, int options);
void	infile_as_stdin(t_shell *shell);
void	outfile_as_stdout(t_shell *shell);
void	input_error(void);
void	error_exit(char *input);
void	perror_exit(char *input);
void	error_no_command(char *argv);

// environment
void	init_env(t_shell *shell, char **envp);
void	print_list_env(t_env *env_list);
void	free_env_list(t_env **list);
void	add_node_to_list_env(t_env **env_list, t_env *new_node);
char	*env_get_var_value(t_shell *shell, char *var);

// builtins
void	ft_echo(char **args, int fd);
int		ft_env(t_shell *shell);
int		execute_builtins(t_shell *shell, char **arguments);
int		ft_pwd(void);
void	ft_unset(t_command *command, t_env **env_list);
void	ft_exit(t_shell *shell);

//signals
void	ft_signals(void);
void	sigquit_handler(int signum);
void	sigint_handler(int signum);

//generic list
t_list	*list_create(t_shell *shell, size_t data_size, func_ptr_free ft_free, func_ptr_comp ft_comp);
void	list_add_new_node(t_shell *shell, t_list *list, void *data);
void	list_remove_head(t_list *list);
void	list_remove_node(t_list *list, void *data);
int		list_get_index(t_list *list, void *data);
void	list_remove_index(t_list *list, int index);
bool	list_contains(t_list *list, void *data);
bool	list_is_identical(t_list *list1, t_list *list2);

//generic list free functions
void	free_node_data(func_ptr_free ft_free, void *data);
t_list	*free_list(t_list *list);
void	free_token(void *data);
void	free_command(void *data);
void	free_redir(void *data);

//generic list compare functions
int		comp_command(void *data1, void *data2);
int		comp_arg(void *data1, void *data2);
int		comp_redir(void *data1, void *data2);
int		comp_token(void *data1, void *data2);

#endif