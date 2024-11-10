/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:00:12 by witong            #+#    #+#             */
/*   Updated: 2024/11/10 11:55:36 by witong           ###   ########.fr       */
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
	char	**cmd_paths;
	char	**cmd_args;
	char	**cmd;
	char	*full_path;
	char	**env;
}		t_pipex;

// utils.c
void	print_error(char *str);
void	print_perror(char *str);
void	init_pipex(t_pipex *px);
void	parent_free(t_pipex *px);
void	child_free(t_pipex *px);

// getpath.c
void	find_path(t_pipex *px);
void	get_cmds(t_pipex *px);

#endif
