/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:43:18 by witong            #+#    #+#             */
/*   Updated: 2024/10/28 03:50:20 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
typedef struct s_pipex_params
{
	char	*infile;
	char	*outfile;
	char	**cmds;
	int		nb_cmds;
	bool	mode;
	char	**envp;
	int		input_fd;
	int		output_fd;
} t_pipex_params;
*/

#include "pipex.h"

bool	get_mode(int ac, char **av)
{
	if (ac < 5 || (strncmp(av[1], "here_doc", 8) == 0 && ac < 6))
	{
		print_error("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n\
			OR ./pipex here_doc <LIMITER> <cmd> <cmd1> <file>");
		return (false);
	}
	return (strncmp(av[1], "here_doc", 8) == 0);
}

void	open_files(t_pipex_params *params)
{
	if (params->mode)
	{
		params.input_fd = here_doc(params.cmds[-1]);
		params.output_fd = open(params->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		params.input_fd = open(params->infile, O_RDONLY);
		if (input_fd < 0)
			print_error("Error opening input file");
		params.output_fd = open(params->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (params.output_fd < 0)
		print_error("Error opening output file");
}
/*
pipex()
{
pipe()
 |
 |-- fork()
      |
      |-- child // cmd1
      :     |--dup2()
      :     |--close end[0]
      :     |--execve(cmd1)
      :
      |-- parent // cmd2
            |--dup2()
            |--close end[1]
            |--execve(cmd2)
}
*/

int	main(int ac, char **av, char **envp)
{
	t_pipex_params	params;

	params.mode = get_mode(ac, av);
	if (params.mode)
	{
		params.infile = NULL;
		params.outfile = av[ac - 1];
		params.nb_cmds = ac - 4;
		params.cmds = &av[3];
	}
	else
	{
		params.infile = av[1];
		params.outfile = av[4];
		params.nb_cmds = 2;
		params.cmds = &av[2];
	}
	params.envp = envp;
	open_files(&params);
	pipex();
	execute();
	return (0);
}
