/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:45:55 by ledio             #+#    #+#             */
/*   Updated: 2024/12/06 23:42:12 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/include/libft.h"

typedef struct pipex_bonus
{
	char		**argv;
	char		**envp;
	int			infile;
	int			outfile;
	int			fd[2];
	int			argc;
}	t_pipex;

void		error_handling(const char *message);
int			open_files(char *file, int number);
char		*costum_getenv(char **envp);
char		*parse_path(char *path, char *command);
void		free_memory(char **dir);
void		initialize_struct(t_pipex *pipex, int argc, char **argv,
				char **envp);
void		initialize_here_doc(t_pipex *pipex, int argc, char **argv,
				char **envp);

#endif