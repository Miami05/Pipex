/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:32:40 by ledio             #+#    #+#             */
/*   Updated: 2024/12/07 21:32:04 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	initialize_struct(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->infile = open_files(argv[1], 0);
	pipex->outfile = open_files(argv[argc - 1], 1);
}

void	initialize_here_doc(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->infile = -1;
	pipex->outfile = open_files(argv[argc - 1], 2);
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
}
