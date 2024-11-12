/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:19:28 by witong            #+#    #+#             */
/*   Updated: 2024/11/12 15:20:59 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	init_ppx(t_pipex *ppx)
{
	ppx->infile = -1;
	ppx->outfile = -1;
	ppx->fd[0] = -1;
	ppx->fd[1] = -1;
	ppx->pid1 = -1;
	ppx->pid2 = -1;
	ppx->cmd = NULL;
	ppx->full_path = NULL;
}

void	close_fds(t_pipex *ppx)
{
	if (ppx->infile >= 0)
		close(ppx->infile);
	if (ppx->outfile >= 0)
		close(ppx->outfile);
	if (ppx->fd[0] >= 0)
		close(ppx->fd[0]);
	if (ppx->fd[1] >= 0)
		close(ppx->fd[1]);
}

void	free_all(t_pipex *ppx)
{
	int	i;

	close_fds(ppx);
	if (ppx->cmd)
	{
		i = 0;
		while (ppx->cmd[i])
			free(ppx->cmd[i++]);
		free(ppx->cmd);
	}
	if (ppx->full_path)
		free(ppx->full_path);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}
