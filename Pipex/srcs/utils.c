/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:23:43 by witong            #+#    #+#             */
/*   Updated: 2024/10/28 08:42:50 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	here_doc_mode(char *limiter)
{
	int	pipefd[2];
	char *line;
	if (pipe(pipefd) == -1)
		print_error("Error pipe issue");
	while(1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

