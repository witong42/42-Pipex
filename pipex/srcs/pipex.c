/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:23:30 by witong            #+#    #+#             */
/*   Updated: 2024/11/08 19:26:57 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_path(t_pipex *params)
{
	char	*tmp_path;
	int		i;

	i = 0;
	while (params->env[i])
	{
		if (params->env[i][0] == 'P')
		{
			tmp_path = ft_strnstr(params->env[i], "PATH=", 5);
			if (tmp_path)
			{
				params->path = ft_split(tmp_path + 5, ':');
				if (params->path == NULL)
					print_error("Error splitting PATH\n");
				return ;
			}
		}
		i++;
	}
	print_error("Error find path failure\n");
}
void	execute(t_pipex *params, int current)
{
	char	**cmd;
	char	*path;
	char	*full_path;
	int		i;

	find_path(params);
	cmd = ft_split(params->cmds[current], ' ');
	if(!cmd || !cmd[0])
		print_error("Error malloc split");
	i = 0;
	while (params && params->path[i])
	{
	path = ft_strjoin(params->path[i], "/");
	full_path = ft_strjoin(path, cmd[0]);
	free(path);
	if (access(full_path, X_OK) == 0)
		break;
	free(full_path);
	i++;
	}
	close(params->input_fd);
	close(params->output_fd);
	execve(full_path, cmd, params->env);
}


void child_process(t_pipex *params, int *fd, int is_first)
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
	free_params(params);
	exit(EXIT_FAILURE);
}

void	pipex(t_pipex *params)
{
	int	fd[2];
	pid_t pid;

	if (pipe(fd) == -1)
		print_error("Error pipe failure\n");
	pid = fork();
	if (pid == -1)
		print_error("Error fork failure\n");
	if (pid == 0)
		child_process(params, fd, 1);
	waitpid(pid, NULL, 0);
	child_process(params, fd, 0);
	close(fd[0]);
	close(fd[1]);
	waitpid(0, NULL, 0);
}

t_pipex	*init(char **av, char **env)
{
	t_pipex *params;

	params = (t_pipex *)malloc(sizeof(t_pipex));
	if (!params)
		print_error("Memory allocation failed");
	params->cmds = &av[2];
	params->env = env;
	params->input_fd = open(av[1], O_RDONLY, 0644);
	if (params->input_fd < 0)
		print_error("Error opening infile\n");
	params->output_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (params->output_fd < 0)
	{
		close(params->input_fd);
		print_error("Error opening outfile\n");
	}
	return (params);
}

int main(int ac, char **av, char **env)
{
	t_pipex	*params;

	if (ac >= 5)
	{
		params = init(av, env);
		pipex(params);
	}
	return (0);
}
