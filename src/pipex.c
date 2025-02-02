/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:55:06 by ledio             #+#    #+#             */
/*   Updated: 2024/12/01 15:44:12 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_child_process(char **argv, char **envp, int *fd)
{
	int			outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
	{
		perror("Error: Opening the file");
		exit(1);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("Error: Duplicating the STDIN file");
		exit(1);
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		perror("Error: Duplicating the STDOUT file");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execute(argv[3], envp);
}

void	first_child_process(char **argv, char **envp, int *fd)
{
	int			infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		perror("Error: Opening the file");
		exit(1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("Error: Duplicating the STDOUT file");
		exit(1);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("Error: Duplicating the STDIN file");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	close(infile);
	execute(argv[2], envp);
}

void	parse_left_arguments(char **argv, char **envp, int *fd)
{
	pid_t			pid1;

	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Error forking process");
		exit(1);
	}
	else if (pid1 == 0)
		first_child_process(argv, envp, fd);
}

void	parse_right_arguments(char **argv, char **envp, int *fd)
{
	pid_t		pid2;

	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Error forking process");
		exit(1);
	}
	else if (pid2 == 0)
		second_child_process(argv, envp, fd);
}

int	main(int argc, char **argv, char **envp)
{
	int				fd[2];
	pid_t			pid1;
	pid_t			pid2;

	pid1 = -1;
	pid2 = -1;
	if (argc != 5)
	{
		perror("Usage ./pipex <infile> <cmd1> <cmd2> <outfile>");
		exit(1);
	}
	if (pipe(fd) == -1)
	{
		perror("Error creating pipex");
		exit(1);
	}
	parse_left_arguments(argv, envp, fd);
	parse_right_arguments(argv, envp, fd);
	close (fd[0]);
	close (fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
