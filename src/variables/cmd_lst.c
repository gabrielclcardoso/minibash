/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcorreia <gcorreia@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:02:11 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/25 14:38:13 by gcorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_lst	*ft_cmd_new(char *line)
{
	t_cmd_lst	*lst;

	lst = malloc(sizeof(t_cmd_lst));
	if (!lst)
		return (NULL);
	lst->filename = NULL;
	lst->input = 0;
	lst->output = 1;
	lst->line = line;
	lst->next = NULL;
	lst->has_truncate = 0;
	lst->delimiter = NULL;
	return (lst);
}

void	ft_cmdadd_back(t_cmd_lst **head, t_cmd_lst *new)
{
	t_cmd_lst	*temp;

	if (!*head || !head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

//void	ft_cmdclear(t_cmd_lst **head)
//{
//	t_cmd_lst	*ptr;
//
//	ptr = *head;
//	while (ptr)
//	{
//		free(ptr->name);
//		free(ptr->content);
//		ptr = ptr->next;
//		free(*head);
//		*head = ptr;
//	}
//}
