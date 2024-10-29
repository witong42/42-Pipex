/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:22:07 by witong            #+#    #+#             */
/*   Updated: 2024/10/29 14:23:30 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex_params	init_params(char **av, char **env)
{
	t_pipex_params params;
	params.infile = av[1];
	params.outfile = av[4];
	params.cmds = &av[2];
//	params.nb_cmds = 2;
	params.env = env;
	return (params);
}
void	open_files(t_pipex_params *params)
{
	params->input_fd = open(params->infile, O_RDONLY, 0644);
	if (params->input_fd < 0)
		print_error("Error opening infile\n");
	params->output_fd = open(params->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (params->output_fd < 0)
	{
		close(params->output_fd);
		print_error("Error opening outfile\n");
	}
}
void	find_path(t_pipex_params *params)
{
	char	*path;
	int		i;

	i = 0;
	while (params->env[i])
	{
		if (params->env[i][0] == 'P')
		{
			path = ft_strnstr(params->env[i], "PATH=", 5);
			if (path)
			{
				params->path = ft_split(path + 5, ':');
				if (params->path == NULL)
					print_error("Error splitting PATH\n");
				return ;
			}
		}
		i++;
	}
	print_error("Error find path failure\n");
}
void	execute(t_pipex_params *params, int current)
{
	char	**cmd;
	char	*path;
	char	*full_path;
	int		i;

	cmd = ft_split(params->cmds[current], ' ');
	if(!cmd || !cmd[0])
		print_error("Error malloc split");
	i = 0;
	while (params->path[i])
	{
	path = ft_strjoin(params->path[i], "/");
	full_path = ft_strjoin(path, cmd[0]);
	free(path);
	if (access(full_path, X_OK) == 0)
		break;
	free(full_path);
	i++;
	}
	execve(full_path,cmd,params->env);
	//TODO free and error
}
void child(t_pipex_params *params, int *fd, int is_first)
{
	if (is_first)
	{
		if (dup2(fd[1], 1) == -1)
			print_error("Error dup2 failure");
		if (dup2(params->input_fd, 0) == -1)
			print_error("Error dup2 failure");
		close(fd[0]);
		close(fd[1]);
		execute(params, 0);
	}
	else
	{
		if (dup2(params->output_fd, 1) == -1)
			print_error("Error dup2 failure");
		if (dup2(fd[0], 0) == -1)
			print_error("Error dup2 failure");
		close(fd[0]);
		close(fd[1]);
		execute(params, 1);
	}
	exit(0);
}

int main(int ac, char **av, char **env)
{
	t_pipex_params params;
	int fd[2];
	pid_t pid;

	if (ac == 5)
	{
		params = init_params(av, env);
		open_files(&params);
		find_path(&params);
		if (pipe(fd) == -1)
			print_error("Error pipe failure\n");
		pid = fork();
		if (pid == -1)
			print_error("Error fork failure\n");
		if (pid == 0)
			child(&params, fd, 1);
		waitpid(pid, NULL, 0);
		child(&params, fd, 0);
		close(fd[0]);
		close(fd[1]);
		waitpid(0, NULL, 0);
	}
}