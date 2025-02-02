/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:24:35 by ledio             #+#    #+#             */
/*   Updated: 2024/12/08 18:35:58 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **dir)
{
	int			i;

	i = 0;
	while (dir[i] != NULL)
	{
		free (dir[i]);
		i++;
	}
	free (dir);
}

char	*parse_path(char *path, char *command)
{
	char		**dir;
	char		*full_path;
	int			i;
	char		*temp;

	dir = ft_split(path, ':');
	if (!dir)
		return (NULL);
	i = 0;
	while (dir[i] != NULL)
	{
		temp = ft_strjoin(dir[i], "/");
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_split(dir);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(dir);
	return (NULL);
}

char	*costum_getenv(char **envp)
{
	int			i;
	char		*path;

	if (!envp)
		return (NULL);
	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	error_handler(const char *message)
{
	perror(message);
	exit(1);
}

void	execute(char *command, char **envp)
{
	char		*path;
	char		*full_path;
	char		**cmd_args;

	cmd_args = ft_split(command, ' ');
	path = costum_getenv(envp);
	if (!path)
		error_handler("Error getting the path");
	full_path = parse_path(path, cmd_args[0]);
	if (full_path != NULL)
	{
		if (execve(full_path, cmd_args, envp) == -1)
		{
			free_split(cmd_args);
			free(full_path);
			error_handler("Error executing the file");
		}
	}
	else
	{
		free_split(cmd_args);
		free(full_path);
		error_handler("Command not found");
	}
}
