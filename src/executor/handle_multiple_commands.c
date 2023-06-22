#include "../../include/minishell.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int handle_fds(int *pipe_fd, int read_end)
{
    if (close(pipe_fd[WRITE_END]) == FAILED)
        perror_exit("4: close");
		
    if (read_end != STDIN_FILENO) 
    {
        if (close(read_end) == FAILED)
            perror_exit("3: close");
    }
	read_end = pipe_fd[READ_END];
    return (read_end);
}
static int	execute_last_command(t_shell *shell, int read_end, char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	if (pid == SUCCES)
	{
		if (dup2(read_end, STDIN_FILENO) == FAILED)
			perror_exit("3: dup2");
		run_command(shell, cmd); 
	}	
	if (close(read_end) == FAILED)
		perror_exit("2: close");
	return(pid);
}

static void execute_child(t_shell *shell, int read_end, int *pipe_fd, char *cmd)
{
	if (dup2(read_end, STDIN_FILENO) == FAILED)
		perror_exit("2: dup2");
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == FAILED)
		perror_exit("1: dup2");
	run_command(shell, cmd);
	if (close(pipe_fd[WRITE_END]) == FAILED)
		perror_exit("1: close");
}

static int	initiate_forks(t_shell *shell, int nb_commands, char **argv)
{
	int 	pipe_fd[2];
	pid_t	pid;
	int		read_end;
	int		index_command = 2;
	
	while(nb_commands) 
	{
	if (pipe(pipe_fd) == FAILED)
		perror_exit("pipe");
	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	if (pid == SUCCES)
		execute_child(shell, read_end, pipe_fd, argv[index_command]);
	read_end = handle_fds(pipe_fd, read_end);
		nb_commands--;
		index_command++;
	}
	pid = execute_last_command(shell, read_end, argv[index_command]);
	return(pid);
}

void	handle_multiple_commands(t_shell *shell, int nb_commands, char **argv)
{
	pid_t	pid;
	
	// save_std(shell->executor);
	pid = initiate_forks(shell, nb_commands, argv);
	// restore_std(shell->executor);
	if (waitpid(pid, NULL, 0) == FAILED)
		perror_exit("waitpid");
}
