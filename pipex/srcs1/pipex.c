/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pipex.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: witong <witong@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/10 08:47:51 by witong			#+#	#+#			 */
/*   Updated: 2024/11/10 09:12:32 by witong		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

//void	execute_command(char *cmd, t_pipex *px)

void	first_child(t_pipex *px, char *cmd)
{
	close(px->fd[0]);
	dup2(px->infile, 0);
	dup2(px->fd[1], 1);
	close(px->infile);
	close(px->fd[1]);
	printf("%s", cmd);
//	execute_command(cmd, px);
}

void	second_child(t_pipex *px, char *cmd)
{
	close(px->fd[1]);
	dup2(px->fd[0], 0);
	dup2(px->outfile, 1);
	close(px->outfile);
	close(px->fd[0]);
	printf("%s", cmd);
//	execute_command(cmd, px);
}

void	pipex(char **av, char **env)
{
	t_pipex px;
	px.infile = open(av[1], O_RDONLY);
	px.outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	px.env = env;

	if (px.infile == -1 || px.outfile == -1)
		print_error("Error open file");
	if (pipe(px.fd) == -1)
		print_error("Error pipe");
	px.pid1 = fork();
	if (px.pid1 < 0)
		print_error("Error Fork");
	if (px.pid1 == 0)
		first_child(&px, av[2]);
	px.pid2 = fork();
	if (px.pid2 < 0)
		print_error("Error Fork");
	if (px.pid2 == 0)
		second_child(&px, av[3]);
	close(px.fd[0]);
	close(px.fd[1]);
	close(px.infile);
	close(px.outfile);
	waitpid(px.pid1, NULL, 0);
	waitpid(px.pid2, NULL, 0);
}

int main(int ac, char **av, char **env)
{
	t_pipex *px;

	if (ac != 5)
		print_perror("Invalid number of arguments.\n");
	pipex(px, av, env);
	fork_children(px);
	return (EXIT_SUCCESS);
}
