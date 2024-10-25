/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:26:07 by witong            #+#    #+#             */
/*   Updated: 2024/10/25 15:36:55 by witong           ###   ########.fr       */
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
*/

#include "pipex.h"

execute()
{
	pipe
	fork
	if (child)
	{
		dup2()
		execve()
	}
	else
		cleanup
}

//void	child(int fd, char **av, char **env)
{
	int	infile;

	infile = open(av[1], O_RDONLY, 0777)
	if (infile < 0)
		print_error("Error opening infile");
	dup2();
	dup2();
	close(fd[0]);
	close(infile);
	execute
}

//void 	parent

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (ac >= 5)
		print_error("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
	if (pipe(fd) < 0)
		print_error("Error creating pipe\n");
	pid = fork();
	if (pid <= 0)
		print_error("Error forking process\n");
	if (pid == 0)
		child(fd, av, env);
	waitpid(pid, NULL. 0);
	parent();
	cleanup();
	return (0);
}
// https://github.com/gabcollet/pipex/blob/master/srcs/pipex_bonus.c


