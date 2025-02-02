/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:48:56 by ledio             #+#    #+#             */
/*   Updated: 2024/12/07 21:43:45 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_command(char *command, char **envp)
{
	char		*path;
	char		*full_path;
	char		**cmd_arg;

	cmd_arg = ft_split(command, ' ');
	path = costum_getenv(envp);
	if (!path)
		error_handling("Error path");
	full_path = parse_path(path, cmd_arg[0]);
	if (full_path != NULL)
	{
		if (execve(full_path, cmd_arg, envp) == -1)
		{
			error_handling("Error executing the file");
			free_memory(cmd_arg);
			free (full_path);
		}
	}
	else
		error_handling("Command not found");
	free_memory (cmd_arg);
	free (full_path);
}

void	parse_pipe(t_pipex *pipex, int i)
{
	pid_t		pid;

	while (i < pipex->argc - 2)
	{
		if (pipe(pipex->fd) == -1)
			error_handling("Error: Creating the pipes");
		pid = fork();
		if (pid == -1)
			error_handling("Error: Forking the pid");
		if (pid == 0)
		{
			close(pipex->fd[0]);
			dup2(pipex->fd[1], STDOUT_FILENO);
			execute_command(pipex->argv[i], pipex->envp);
		}
		else
		{
			close(pipex->fd[1]);
			dup2(pipex->fd[0], STDIN_FILENO);
		}
		i++;
	}
}

void	parse_here_doc(char *delimeter, int *fd)
{
	char		*line;

	close(fd[0]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0)
		{
			free (line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free (line);
	}
}

void	here_doc(t_pipex *pipex)
{
	pid_t		pid;

	if (pipe(pipex->fd) == -1)
		error_handling("Error: Creating the pipes");
	pid = fork();
	if (pid == -1)
		error_handling("Error: Forking pid");
	if (pid == 0)
	{
		parse_here_doc(pipex->argv[2], pipex->fd);
		exit(0);
	}
	close(pipex->fd[1]);
	waitpid(pid, NULL, 0);
	dup2(pipex->fd[0], STDIN_FILENO);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex			pipex;

	if (argc < 5)
	{
		perror("Usage: ./pipex_bonus <command1> <command2> ... <outfile>");
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			error_handling("Usage: ./pipex_bonus "
				"[here_doc LIMITER <cmd1> <cmd2> ... outfile]");
		initialize_here_doc(&pipex, argc, argv, envp);
		here_doc(&pipex);
		parse_pipe(&pipex, 3);
	}
	else
	{
		initialize_struct(&pipex, argc, argv, envp);
		dup2(pipex.infile, STDIN_FILENO);
		parse_pipe(&pipex, 2);
	}
	dup2(pipex.outfile, STDOUT_FILENO);
	execute_command(pipex.argv[argc - 2], pipex.envp);
}
