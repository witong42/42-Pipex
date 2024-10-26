/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:23:43 by witong            #+#    #+#             */
/*   Updated: 2024/10/26 15:48:36 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	cleanup(char **array)
{
	if(!array)
		return ;
	while (*array++)
		free(*array++);
	free(array);
}

char	*find_path(char *cmd, char **env)
{
	return(NULL);
}


void	execute(int ac, char **av, char **env)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(*av, ' ');
	if (!cmds)
		print_error("Error split malloc failed");
	path = find_path(cmds[0], env);
	if(!path)
		cleanup(&path);

}

