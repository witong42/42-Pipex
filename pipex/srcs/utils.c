/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: witong <witong@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/25 14:23:43 by witong			#+#	#+#			 */
/*   Updated: 2024/11/10 11:18:15 by witong		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	return ;
}

void	print_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
void init_pipex(t_pipex *px)
{
    px->infile = -1;
    px->outfile = -1;
    px->fd[0] = -1;
    px->fd[1] = -1;
    px->pid1 = -1;
    px->pid2 = -1;
    px->cmd_paths = NULL;
    px->cmd_args = NULL;
    px->cmd = NULL;
    px->full_path = NULL;
    px->env = NULL;
}

void parent_free(t_pipex *px)
{
	int i;

	if (px->infile > 0)
		close(px->infile);
	if (px->outfile > 0)
		close(px->outfile);
	if (px->cmd_paths)
	{
		i = 0;
		while (px->cmd_paths[i])
		{
			free(px->cmd_paths[i]);
			i++;
		}
		free(px->cmd_paths);
	}
	if (px->full_path)
		free(px->full_path);
}

void child_free(t_pipex *px)
{
	int i;

	if (px->cmd_args)
	{
		i = 0;
		while (px->cmd_args[i])
		{
			free(px->cmd_args[i]);
			i++;
		}
		free(px->cmd_args);
	}
	if (px->cmd)
	{
		i = 0;
		while (px->cmd[i])
		{
			free(px->cmd[i]);
			i++;
		}
		free(px->cmd);
	}
}
