/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:00:12 by witong            #+#    #+#             */
/*   Updated: 2024/11/12 15:20:38 by witong           ###   ########.fr       */
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
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd;
	char	*full_path;
}		t_pipex;

// utils.c
void	print_error(char *str);
void	init_ppx(t_pipex *ppx);
void	close_fds(t_pipex *ppx);
void	free_all(t_pipex *ppx);
void	free_paths(char **paths);

// getpath.c
void	get_cmds(t_pipex *ppx, char **env);

#endif
