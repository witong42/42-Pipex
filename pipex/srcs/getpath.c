/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:00:22 by witong            #+#    #+#             */
/*   Updated: 2024/11/10 11:48:10 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_path(t_pipex *px)
{
	char **env = px->env;

	while (*env && ft_strncmp("PATH=", *env, 5) != 0)
		env++;
	if (!*env)
		print_error("Error finding PATH variable\n");
	px->cmd_paths = ft_split(*env + 5, ':');
	if (!px->cmd_paths)
		print_error("Error splitting PATH\n");
}

void	get_cmds(t_pipex *px)
{
	char	*path;
	char	*full_path;
	int		i;

	find_path(px);
	i = 0;
	while (px->cmd_paths[i])
	{
		path = ft_strjoin(px->cmd_paths[i], "/");
		full_path = ft_strjoin(path, px->cmd[0]);
		free(path);
		if (access(full_path, X_OK) == 0)
		{
			px->full_path = full_path;
			return ;
		}
		free(full_path);
		i++;
	}
	print_perror("Command not found\n");
}
