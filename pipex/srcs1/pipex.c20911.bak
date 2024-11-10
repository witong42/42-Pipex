#include "pipex.h"

void	get_cmds(t_pipex *params, char *cmd)
{
	char *path;
	char *full_path;

	while (*params->paths)
	{
		path = ft_strjoin(*params->paths, "/");
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (access(full_path, 0) == 0)
		{
			params->full_path = full_path;
			return ;
		}
		free(full_path);
		params->paths++;
	}
	print_perror("Command not found");
}

void first_child(t_pipex *params, int *fd)
{
	if (dup2(fd[1], 1) == -1)
		print_error("Error dup2 failure");
	close(fd[1]);
	if (dup2(params->infile, 0) == -1)
		print_error("Error dup2 failure");
	close(fd[0]);
	params->cmd_args = ft_split([0], ' ');
	get_cmds(params, params->cmd[0]);
	execve(params->full_path, params->cmd, params->env);
	print_perror("Error execve\n");
}
void second_child(t_pipex *params, int *fd)
{
	if (dup2(params->outfile, 1) == -1)
		print_error("Error dup2 failure");
	close(fd[1]);
	if (dup2(fd[0], 0) == -1)
		print_error("Error dup2 failure");
	close(fd[0]);
	params->cmd = ft_split(av[3], ' ');
	if (!params->cmd)
		print_error("Error split failed.\n");
	get_cmds(params, params->cmd[1]);
	execve(params->full_path, params->cmd, params->env);
	print_perror("Error execve\n");
}
void	find_path(t_pipex *params)
{
	char **env;

	env = params->env;
	while (*env && ft_strncmp("PATH=", *env, 5) != 0)
		env++;
	if (!*env)
		print_error("Error finding PATH variable\n");
	params->paths = ft_split(*env + 5, ':');
	if (!params->paths)
		print_error("Error splitting PATH\n");
}

void	pipex(t_pipex *params)
{
	int	fd[2];
	pid_t child1;
	pid_t child2;

	if (pipe(fd) == -1)
		print_perror("Error Pipe.\n");
	child1 = fork();
	if (child1 == -1)
		print_error("Error Fork.\n");
	if (child1 == 0)
		first_child(params, fd);
	child2 = fork();
	if (child2 == -1)
		print_error("Error Fork.\n");
	if (child2 == 0)
		second_child(params, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
}

t_pipex	*init(char **av, char **env)
{
	t_pipex *params;

	params = malloc(sizeof(t_pipex));
	if (!params)
		print_error("Memory allocation failed\n");
	params->env = env;
	params->cmd = &av[2];
	params->infile = open(av[1], O_RDONLY);
	if (params->infile < 0)
		print_perror("Error Infile.\n");
	params->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (params->outfile < 0)
	{
		close(params->infile);
		print_perror("Error Outfile.\n");
	}
	find_path(params);
	return (params);
}

int main(int ac, char **av, char **env)
{
	t_pipex	*params;

	if (ac != 5)
		print_perror("Invalid number of arguments.\n");
	params = init(av, env);
	pipex(params);
	free_params(params);
	return (0);
}
