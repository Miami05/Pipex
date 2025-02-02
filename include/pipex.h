/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:54:30 by ledio             #+#    #+#             */
/*   Updated: 2024/12/05 20:14:01 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/include/libft.h"

void	execute(char *command, char **envp);

#endif