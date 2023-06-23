#include "../include/minishell.h"
#include <signal.h>

// for testing puropses

void	exit_lexer(t_shell *shell)
{
	free_list(shell->lexer);
	print_list(shell->expander);
	free_list(shell->expander);
}

void	inthandler(int signum) // for testing purpose
{
	if (signum == SIGINT)
		exit(EXIT_SUCCESS);
}
void	f(void)
{
	system("leaks minishell");
}

void	make_var_list(t_shell *shell) //for testing purpose
{
	t_var *new;

	new = malloc(sizeof(t_var));
	new->name = "VAR";
	new->value = "value";
	new->next = NULL;
	shell->var_list = new;
}

// executor tester
int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void) argv;
	(void) envp;
	if (argc > 1)
		;//exit
	atexit(f);
	signal(SIGINT, &inthandler);
	ft_bzero(&shell, sizeof(t_shell));
	while (1)
	{
		make_var_list(&shell); //for testing purpose
		shell.cmd_line = readline("shellyeah$ ");
		add_history(shell.cmd_line);
		shell.lexer = lexer(&shell);
		shell.expander = expander(&shell);
		exit_lexer(&shell);//remove later
		shell.lexer = NULL;
		shell.expander = NULL;
		free(shell.cmd_line);
		free(shell.var_list); //remove later
	}

// main to test executor

// int main(int argc, char **argv, char **envp)
// {
// 	t_shell shell;

// 	if(argc != 4) //1 cmd
// 	{
// 		ft_putstr_fd("wrong argument input", 1);
// 		exit(EXIT_FAILURE);
// 	}
// 	input_handling(&shell, argc, argv, envp);
// 	infile_as_stdin(&shell);
// 	outfile_as_stdout(&shell);
// 	create_single_child(&shell);
// 	// argc -= 4;
// 	// handle_multiple_commands(&shell, argc, argv); 
// 	return(0);
// }

// main to test envp

int	main(int argc,)

}