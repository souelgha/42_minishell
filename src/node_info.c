/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:44:19 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/04 13:12:23 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

t_redirect	*new_node_info(void)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->red = NULL;
	new->token = 0;
	new->fd_here_doc = -1;
	new->next = NULL;
	return (new);
}

t_redirect	*add_node_info(t_redirect **info, int size)
{
	t_redirect	*tmp;

	if (size == 0)
		return (NULL);
	if (!(*info))
	{
		*info = new_node_info();
		if (!(*info))
			return (NULL);
		(*info)->next = NULL;
		(*info)->red = malloc((size) * sizeof(char));
		if (!(*info)->red)
			return (NULL);
		tmp = *info;
		return (tmp);
	}
	else
	{
		tmp = help_node_info(info, size);
		return (tmp);
	}
}

t_redirect	*help_node_info(t_redirect **info, int size)
{
	t_redirect	*tmp;

	tmp = *info;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node_info();
	if (!tmp->next)
		return (NULL);
	tmp = tmp->next;
	tmp->red = malloc((size) * sizeof(char));
	if (!tmp->red)
		return (NULL);
	return (tmp);
}
