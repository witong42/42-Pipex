/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pipex.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: witong <witong@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/10 08:47:51 by witong			#+#	#+#			 */
/*   Updated: 2024/11/10 09:12:32 by witong		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

void first_child(t_pipex *px, int pipe_fd[2])
{
	if (dup2(pipe_fd[1], 1) == -1)
		print_error("Error dup2 failed");
	close(pipe_fd[1]);
	if (dup2(px->infile, 0) == -1)
		print_error("Error dup2 failed");
	close(pipe_fd[0]);
	px->cmd = ft_split(px->cmd_args[0], ' ');
	if (!px->cmd)
		print_error("Error split failed.\n");
	get_cmds(px);
	execve(px->full_path, px->cmd, px->env);
	print_perror("Error execve failed\n");
}

void second_child(t_pipex *px, int pipe_fd[2])
{
	if (dup2(px->outfile, 1) == -1)
		print_error("Error dup2 failed");
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], 0) == -1)
		print_error("Error dup2 failed");
	close(pipe_fd[0]);
	px->cmd = ft_split(px->cmd_args[1], ' ');
	if (!px->cmd)
		print_error("Error split failed.\n");
	get_cmds(px);
	execve(px->full_path, px->cmd, px->env);
	print_perror("Error execve failed\n");
}


static void	pipex(t_pipex *px, char **av, char **env)
{
	px->infile = open(av[1], O_RDONLY);
	px->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->infile == -1 || px->outfile == -1)
		print_perror("Error opening files\n");
	px->cmd_args = &av[2];
	px->env = env;
}

static void	fork_children(t_pipex *px)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		print_perror("Error pipe failed\n");
	pid1 = fork();
	if (pid1 == -1)
		print_perror("Error fork failed\n");
	if (pid1 == 0)
		first_child(px, pipe_fd);
	pid2 = fork();
	if (pid2 == -1)
		print_perror("Error fork failed\n");
	if (pid2 == 0)
		second_child(px, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	parent_free(px);
}

int main(int ac, char **av, char **env)
{
	t_pipex *px;

	if (ac != 5)
		print_perror("Invalid number of arguments.\n");
	px = malloc(sizeof(t_pipex));
	if (!px)
		print_error("Error memory allocation\n");
	init_pipex(px);
	pipex(px, av, env);
	fork_children(px);
	return (EXIT_SUCCESS);
}
