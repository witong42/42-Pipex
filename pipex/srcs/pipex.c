/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pipex.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: witong <witong@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/01 14:23:39 by witong			#+#	#+#			 */
/*   Updated: 2024/11/10 14:24:44 by witong		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

void child_process(t_pipex *ppx, char **av, char **env)
{
	dup2(ppx->infile, 0);
	dup2(ppx->fd[1], 1);
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	close(ppx->infile);
	close(ppx->outfile);
	get_cmds(ppx, env, av[2]);
	execve(ppx->full_path, ppx->cmd, env);
	print_error("Error executing command");
}

void parent_process(t_pipex *ppx, char **av, char **env)
{
	waitpid(ppx->pid, NULL, 0);
	dup2(ppx->fd[0], 0);
	dup2(ppx->outfile, 1);
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	close(ppx->infile);
	close(ppx->outfile);
	get_cmds(ppx, env, av[3]);
	execve(ppx->full_path, ppx->cmd, env);
	print_error("Error executing command");
}

void pipex(t_pipex *ppx, char **av, char **env)
{
	ppx->infile = open(av[1], O_RDONLY);
	ppx->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ppx->infile < 0 || ppx->outfile < 0)
		print_error("Error opening files");
	if (pipe(ppx->fd) == -1)
		print_error("Error creating pipe");
	ppx->pid = fork();
	if (ppx->pid == -1)
		print_error("Error during fork");
	if (ppx->pid == 0)
		child_process(ppx, av, env);
	else
		parent_process(ppx, av, env);
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	close(ppx->infile);
	close(ppx->outfile);
}

int main(int ac, char **av, char **env)
{
	t_pipex ppx;

	if (ac != 5)
		print_error("Usage: ./pipex infile cmd1 cmd2 outfile");
	pipex(&ppx, av, env);
	return (0);
}
