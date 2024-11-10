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

void first_child(t_pipex *px)
{
	if (dup2(px->fd[1], 1) == -1)
		print_error("Error dup2 failed");
	close(px->fd[1]);
	if (dup2(px->infile, 0) == -1)
		print_error("Error dup2 failed");
	close(px->fd[0]);
	px->cmd = ft_split(px->cmd_args[0], ' ');
	if (!px->cmd)
		print_error("Error split failed.\n");
	get_cmds(px);
	execve(px->full_path, px->cmd, px->env);
	child_free(px);
	print_perror("Error execve failed\n");
}

void second_child(t_pipex *px)
{
	if (dup2(px->outfile, 1) == -1)
		print_error("Error dup2 failed");
	close(px->fd[1]);
	if (dup2(px->fd[0], 0) == -1)
		print_error("Error dup2 failed");
	close(px->fd[0]);
	px->cmd = ft_split(px->cmd_args[1], ' ');
	if (!px->cmd)
		print_error("Error split failed.\n");
	get_cmds(px);
	execve(px->full_path, px->cmd, px->env);
	child_free(px);
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
	if (pipe(px->fd) == -1)
	{
		free(px);
		print_perror("Error pipe\n");
	}
}

static void	fork_children(t_pipex *px)
{
	px->pid1 = fork();
	if (px->pid1 == -1)
		print_perror("Error fork failed\n");
	if (px->pid1 == 0)
		first_child(px);
	px->pid2 = fork();
	if (px->pid2 == -1)
		print_perror("Error fork failed\n");
	if (px->pid2 == 0)
		second_child(px);
	close(px->fd[0]);
	close(px->fd[1]);
	waitpid(px->pid1, NULL, 0);
	waitpid(px->pid2, NULL, 0);
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
	parent_free(px);
	return (EXIT_SUCCESS);
}
