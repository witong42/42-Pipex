/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:19:16 by witong            #+#    #+#             */
/*   Updated: 2024/11/12 16:24:52 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_child(t_pipex *ppx, char **av, char **env)
{
	dup2(ppx->infile, STDIN_FILENO);
	dup2(ppx->fd[1], STDOUT_FILENO);
	close_fds(ppx);
	ppx->cmd = ft_split(av[2], ' ');
	if (!ppx->cmd || !ppx->cmd[0])
	{
		free_all(ppx);
		print_error("Error splitting command.\n");
	}
	if (access(ppx->cmd[0], X_OK) == 0)
		execve(ppx->cmd[0], ppx->cmd, env);
	else
	{
		get_cmds(ppx, env);
		execve(ppx->full_path, ppx->cmd, env);
	}
	free_all(ppx);
	print_error("Error execve.\n");
}

static void	second_child(t_pipex *ppx, char **av, char **env)
{
	dup2(ppx->fd[0], STDIN_FILENO);
	dup2(ppx->outfile, STDOUT_FILENO);
	close_fds(ppx);
	ppx->cmd = ft_split(av[3], ' ');
	if (!ppx->cmd || !ppx->cmd[0])
	{
		free_all(ppx);
		print_error("Error splitting command.\n");
	}
	if (access(ppx->cmd[0], X_OK) == 0)
		execve(ppx->cmd[0], ppx->cmd, env);
	else
	{
		get_cmds(ppx, env);
		execve(ppx->full_path, ppx->cmd, env);
	}
	free_all(ppx);
	print_error("Error execve.\n");
}

static void	open_files(t_pipex *ppx, char **av)
{
	ppx->infile = open(av[1], O_RDONLY);
	ppx->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ppx->infile < 0)
		ft_putstr_fd("Error open infile\n", 2);
	if (ppx->outfile < 0)
	{
		free_all(ppx);
		print_error("Error open outfile.\n");
	}
	if (pipe(ppx->fd) == -1)
	{
		free_all(ppx);
		print_error("Error pipe.\n");
	}
}

static void	pipex(t_pipex *ppx, char **av, char **env)
{
	ppx->pid1 = fork();
	if (ppx->pid1 == -1)
	{
		free_all(ppx);
		print_error("Error fork.\n");
	}
	if (ppx->pid1 == 0)
		first_child(ppx, av, env);
	ppx->pid2 = fork();
	if (ppx->pid2 == -1)
	{
		free_all(ppx);
		print_error("Error fork.\n");
	}
	if (ppx->pid2 == 0)
		second_child(ppx, av, env);
	close_fds(ppx);
	waitpid(ppx->pid1, NULL, 0);
	waitpid(ppx->pid2, NULL, 0);
	free_all(ppx);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	ppx;

	if (ac != 5)
		print_error("Error Invalid number of arguments.\n");
	init_ppx(&ppx);
	open_files(&ppx, av);
	pipex(&ppx, av, env);
	free_all(&ppx);
	return (0);
}
