/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:58:27 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 12:07:00 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

void	free_info_list(t_redirect **info)
{
	t_redirect	*tmp;

	tmp = *info;
	while (tmp)
	{
		*info = tmp->next;
		free(tmp->red);
		free(tmp);
		tmp = *info;
	}
	if (info)
		free(info);
	info = NULL;
}

void	free_command_list(t_command ***command)
{
	t_command	*tmp;

	if (*command)
	{
		if (**command)
		{
			tmp = **command;
			while (tmp)
			{
				**command = tmp->next_command;
				free_arg_list(tmp->arg);
				free_info_list(tmp->info);
				free(tmp);
				tmp = **command;
			}
		}
	}
	if (*command)
		free(*command);
	*command = NULL;
}

void	free_arg_list(t_arg **parsed)
{
	t_arg	*tmp;

	tmp = *parsed;
	while (tmp)
	{
		*parsed = tmp->next;
		free(tmp->str);
		free(tmp);
		tmp = *parsed;
	}
	if (parsed)
		free(parsed);
	parsed = NULL;
}
