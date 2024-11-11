/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:19:16 by witong            #+#    #+#             */
/*   Updated: 2024/11/11 15:34:17 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex *ppx, char **av, char **env)
{
	dup2(ppx->infile, STDIN_FILENO);
	dup2(ppx->fd[1], STDOUT_FILENO);
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	close(ppx->infile);
	close(ppx->outfile);
	ppx->cmd = ft_split(av[2], ' ');
	if (!ppx->cmd || !ppx->cmd[0])
	{
		free_all(ppx);
		print_error("Error splitting command.\n");
	}
	if (access(ppx->cmd[0], X_OK) == 0)
		execve(ppx->cmd[0], ppx->cmd, env);
	get_cmds(ppx, env);
	execve(ppx->full_path, ppx->cmd, env);
	free_all(ppx);
	print_error("Error executing command.\n");
}

void	parent_process(t_pipex *ppx, char **av, char **env)
{
	waitpid(ppx->pid, NULL, 0);
	dup2(ppx->fd[0], STDIN_FILENO);
	dup2(ppx->outfile, STDOUT_FILENO);
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	close(ppx->infile);
	close(ppx->outfile);
	ppx->cmd = ft_split(av[3], ' ');
	if (!ppx->cmd || !ppx->cmd[0])
	{
		free_all(ppx);
		print_error("Error splitting command.\n");
	}
	if (access(ppx->cmd[0], X_OK) == 0)
		execve(ppx->cmd[0], ppx->cmd, env);
	get_cmds(ppx, env);
	execve(ppx->full_path, ppx->cmd, env);
	free_all(ppx);
	print_error("Error executing command.\n");
}

void	pipex(t_pipex *ppx, char **av, char **env)
{
	ppx->infile = open(av[1], O_RDONLY);
	ppx->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ppx->infile < 0 || ppx->outfile < 0)
		print_error("Error open files.\n");
	if (pipe(ppx->fd) == -1)
	{
		free_all(ppx);
		print_error("Error pipe.\n");
	}
	ppx->pid = fork();
	if (ppx->pid == -1)
	{
		free_all(ppx);
		print_error("Error fork.\n");
	}
	if (ppx->pid == 0)
		child_process(ppx, av, env);
	else
		parent_process(ppx, av, env);
	free_all(ppx);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	ppx;

	if (ac != 5)
		print_error("Error Invalid number of arguments.\n");
	init_ppx(&ppx);
	pipex(&ppx, av, env);
	free_all(&ppx);
	return (0);
}
