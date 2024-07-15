/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_do_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:06:16 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/06 11:43:41 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

int	how_much_cmd(t_command **command)
{
	t_command	*tmp;
	int			i;

	tmp = *command;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next_command;
		i++;
	}
	return (i);
}

void	init_info_fd(t_info_fd *fd)
{
	fd->oldfd_in = dup(0);
	fd->oldfd_out = dup(1);
	fd->index = 0;
	fd->fd_0 = -1;
	fd->fdpipe[0] = -1;
	fd->fdpipe[1] = -1;
	fd->bool = -1;
}
