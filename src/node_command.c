/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:55:53 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/14 19:38:18 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

void	add_node_command(t_command **command, t_arg **arg, t_redirect **info)
{
	t_command	*tmp;

	if (!(*command))
	{
		*command = new_node_command();
		if (!(*command))
			return ;
		(*command)->arg = arg;
		(*command)->info = info;
		if (!(*command)->arg)
			return ;
	}
	else
	{
		tmp = *command;
		while (tmp->next_command)
			tmp = tmp->next_command;
		tmp->next_command = new_node_command();
		if (!tmp->next_command)
			return ;
		tmp = tmp->next_command;
		tmp->arg = arg;
		tmp->info = info;
	}
}

t_command	*new_node_command(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->arg = NULL;
	new->info = NULL;
	new->fd_prio.fd_redirect_in = -1;
	new->fd_prio.fd_redirect_out = -1;
	new->fd_prio.fd_redirect_err = -1;
	new->pid = 0;
	new->next_command = NULL;
	return (new);
}
