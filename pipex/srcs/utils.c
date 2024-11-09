/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:23:43 by witong            #+#    #+#             */
/*   Updated: 2024/11/09 17:43:49 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	print_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void free_params(t_pipex *params)
{
	int	i;

	i = 0;
	if (params)
	{
		if (params->infile >= 0)
			close(params->infile);
		if (params->outfile >= 0)
			close(params->outfile);
		if (params->paths)
		{
            while (params->paths[i])
                free(params->paths[i++]);
            free(params->paths);
        }
        free(params);
    }
}

