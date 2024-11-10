/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:48:19 by witong            #+#    #+#             */
/*   Updated: 2024/11/10 15:18:28 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void free_cmd_paths(char **cmd_paths)
{
	int i = 0;

	while (cmd_paths[i])
	{
		free(cmd_paths[i]);
		i++;
	}
	free(cmd_paths);
}

char **find_path(t_pipex *ppx, char **env, char *cmd)
{
	while (*env && ft_strncmp("PATH=", *env, 5) != 0)
		env++;
	if (!*env)
		print_error("Error finding PATH variable\n");
	ppx->cmd = ft_split(cmd, ' ');
	if (!ppx->cmd || !ppx->cmd[0])
		print_error("Error splitting command\n");
	return (ft_split(*env + 5, ':'));
}

void get_cmds(t_pipex *ppx, char **env, char *cmd)
{
	char **paths;
	char *path;
	char *full_path;
	int i;

	paths = find_path(ppx, env, cmd);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path, ppx->cmd[0]);
		free(path);
		if (access(full_path, X_OK) == 0)
		{
			ppx->full_path = full_path;
			free_cmd_paths(paths);
			return;
		}
		free(full_path);
		i++;
	}
	free_cmd_paths(paths);
	print_error("Command not found\n");
}
