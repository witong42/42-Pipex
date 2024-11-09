/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:23:43 by witong            #+#    #+#             */
/*   Updated: 2024/11/09 09:29:41 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void free_params(t_pipex_params *params)
{
	int	i;

	i = 0;
	{
		while (params->cmds[i])
		{
			free(params->cmds[i]);
			i++;
		}
		free(params->cmds);
	}
	i = 0;
	if (params->env)
	{
		while (params->env[i++])
			free(params->env[i]);
		free(params->env);
	}
}

char *find_path(char **envp)
{
	while (*envp && ft_strncmp("PATH=", *envp, 5) != 0)
		envp++;
	if (*envp)
		return *envp + 5;
	else
		return NULL;
}
