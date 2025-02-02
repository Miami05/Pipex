/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:39:52 by ldurmish          #+#    #+#             */
/*   Updated: 2024/12/07 01:57:49 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/**======================================================================= Libraries =======================================================================**/
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "libft.h"

/**=================================================================== Macros and Defines ===================================================================**/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/**=============================================================== Get Next Line Structures =================================================================**/
typedef struct s_gnl_list
{
	char				*data;
	int					len;
	struct s_gnl_list	*next;
	int					to_delete;
	int					found_newline;
}				t_gnl_list;

typedef struct s_glfl
{
	char			*tmp;
	char			*line;
	char			*new_line;
	char			*part;
	t_gnl_list		*temp;
}			t_glfl;

/**====================================================================== Prototypes ====================================================================== **/

/**=============================================================== Get Next Line Functions =============================================================== **/

/*------------------------------------------------------------- Get Next Line Main Function -------------------------------------------------------------*/
char							*get_next_line(int fd);

/*----------------------------------------------------------- Helper functions for Get Next Line -----------------------------------------------------------*/
void							ft_add_node(t_gnl_list **head, char *str);
void							ft_remove_data(t_gnl_list **head);
void							*ft_clear_list(t_gnl_list **list, t_gnl_list *clean_node,
									char *buf, int del_one);
char							*ft_strchr(const char *s, int c);
char							*ft_strdup(const char *str);

#endif
