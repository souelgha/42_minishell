/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:41:49 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/17 15:29:15 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

t_arg	*add_node_arg(t_arg **parsed, int size)
{
	t_arg	*tmp;

	if (size == 0)
		return (NULL);
	if (!*parsed)
	{
		*parsed = new_node();
		if (!(*parsed))
			return (NULL);
		(*parsed)->next = NULL;
		(*parsed)->str = malloc((size) * sizeof(char));
		if (!(*parsed)->str)
		{
			free(*parsed);
			return (NULL);
		}
		tmp = *parsed;
		return (tmp);
	}
	else
	{
		tmp = help_node_arg(parsed, size);
		return (tmp);
	}
}

t_arg	*help_node_arg(t_arg **parsed, int size)
{
	t_arg	*tmp;

	tmp = *parsed;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node();
	if (!tmp->next)
		return (NULL);
	tmp = tmp->next;
	tmp->str = malloc((size) * sizeof(char));
	if (!tmp->str)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

t_arg	*new_node(void)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->next = NULL;
	return (new);
}
