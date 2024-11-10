/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:02:25 by witong            #+#    #+#             */
/*   Updated: 2024/11/10 21:16:28 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_paths(char **paths)
{
	int i = 0;

	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char **find_path(char **env)
{
	while (*env && ft_strncmp("PATH=", *env, 5) != 0)
		env++;
	if (!*env)
		print_error("Error finding PATH variable\n");
	return (ft_split(*env + 5, ':'));
}

static char *find_fullpath(char **paths, char *cmd)
{
	int i;
	char *path;
	char *full_path;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (NULL);
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void get_cmds(t_pipex *ppx, char **env)
{
	char **paths;

	paths = find_path(env);
	if (!paths)
		print_error("Error finding PATH variable\n");
	ppx->full_path = find_fullpath(paths, ppx->cmd[0]);
	free_paths(paths);
	if (!ppx->full_path)
		print_error("Command not found\n");
}
