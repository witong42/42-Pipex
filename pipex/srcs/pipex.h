/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:00:12 by witong            #+#    #+#             */
/*   Updated: 2024/11/09 19:56:28 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		fd[2];
	int		pid1;
	int		pid2;
	char	**cmd_args;
	char	**cmd_paths;
	char	*cmd;
	char	**env;
}		t_pipex;

// utils.c
void	print_error(char *str);
void	print_perror(char *str);
void	free_params(t_pipex *params);

#endif
