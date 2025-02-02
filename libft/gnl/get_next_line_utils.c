/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 23:15:41 by ldurmish          #+#    #+#             */
/*   Updated: 2024/12/07 01:58:13 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/get_next_line.h"

char	*ft_strdup(const char *str)
{
	int			len;
	char		*new_str;

	if (!str)
		return (NULL);
	len = 0;
	new_str = NULL;
	while (str[len] != '\0')
		len++;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	len = 0;
	while (str[len] != '\0')
	{
		new_str[len] = str[len];
		len++;
	}
	new_str[len] = '\0';
	return (new_str);
}

void	ft_add_node(t_gnl_list **head, char *str)
{
	t_gnl_list	*new_node;
	t_gnl_list	**current;

	new_node = malloc(sizeof(t_gnl_list));
	if (!new_node)
		return ;
	new_node->data = ft_strdup(str);
	if (!new_node->data)
	{
		free(new_node);
		return ;
	}
	new_node->found_newline = (ft_strchr(new_node->data, '\n') != NULL);
	new_node->next = NULL;
	current = head;
	while (*current)
		current = &((*current)->next);
	*current = new_node;
}

char	*ft_strchr(const char *s, int c)
{
	int			i;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}

void	*ft_clear_list(t_gnl_list **list, t_gnl_list *clean_node, char *buf,
	int del_one)
{
	t_gnl_list	*tmp;

	if (del_one)
	{
		tmp = *list;
		*list = (*list)->next;
		return (free(tmp->data), free(tmp), NULL);
	}
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->data);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node != NULL && clean_node->data != NULL
		&& clean_node->data[0] != '\0')
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
	return (NULL);
}
