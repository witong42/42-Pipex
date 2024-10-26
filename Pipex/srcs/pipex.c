/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:26:07 by witong            #+#    #+#             */
/*   Updated: 2024/10/26 16:14:24 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
It takes 4 arguments
./pipex file1 cmd1 cmd2 file2
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
Support « and » when the first parameter is "here_doc".
This:
$> ./pipex here_doc LIMITER cmd cmd1 file
Should behave like:
cmd << LIMITER | cmd1 >> file

access("example.txt, R_OK") : checks whether a process has permission to access a file
dup(fd) : dupplicate file descriptors
dup2(fd, STDOUT_FILENO) : replace open file descriptors
execve(cmd, args, env) : is a system call that allows you to execute another program from within your program.
fork
pipe
unlink
wait
waitpid

*/

#include "pipex.h"

void	open_file(int *fd, int ac, char **av, int mode)
{
	if (mode == 1)
	{
		fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[1] < 0)
			print_error("Error opening outfile\n");
	}
	else
	{
		fd[0] = open(av[1], O_RDONLY);
		if (fd[0] < 0)
			print_error("Error opening infile\n");
		fd[1] = open(av[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd[1] < 0)
			print_error("Error opening outfile\n");
	}
}
void	close_file(int *fd, pid_t pid)
{
		waitpid(pid, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute(ac, av, env);
}


	if (mode == 1)
		execve(av[3], &av[3], env);
	else
		execve(av[2], &av[2], env);


void	here_doc(char *limiter, char **av)
{
	while(1)
	{

	}
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid;
	bool	mode;

	mode = (ft_strncmp(av[1], "here_doc", 8) == 0);
    if (ac < 5 || (mode == 1 && ac < 6))
		print_error("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n\
			OR ./pipex here_doc <LIMITER> <cmd> <cmd1> <file>");
	open_file(fd, ac, av, mode);
	if (pipe(fd) < 0)
		print_error("Error creating pipe\n");
	pid = fork();
	if (pid < 0)
		print_error("Error forking process\n");
	if (pid == 0)
		if (mode == 1)
//			here_doc(av[2]);
	return (0);
}


// https://reactive.so/post/42-a-comprehensive-guide-to-pipex/
// https://github.com/gabcollet/pipex/blob/master/srcs/pipex_bonus.c


