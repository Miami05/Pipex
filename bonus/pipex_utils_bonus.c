/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:22:02 by ledio             #+#    #+#             */
/*   Updated: 2024/12/08 18:35:51 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_handling(const char *message)
{
	perror(message);
	exit(1);
}

int	open_files(char *file, int number)
{
	int			fd;

	if (number == 0)
	{
		fd = open(file, O_RDONLY, 0777);
		if (fd == -1)
			error_handling("Error opening the infile");
	}
	else if (number == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT, O_TRUNC, 0777);
		if (fd == -1)
			error_handling("Error opening the oufile");
	}
	else if (number == 2)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			error_handling("Error opening the in_her_doc");
	}
	else
		error_handling("Invalid number");
	return (fd);
}

void	free_memory(char **dir)
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
	char		*temp;
	int			i;

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
			free_memory(dir);
			return (full_path);
		}
		free (full_path);
		i++;
	}
	free_memory(dir);
	return (NULL);
}

char	*costum_getenv(char **envp)
{
	int		i;
	char	*path;

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
