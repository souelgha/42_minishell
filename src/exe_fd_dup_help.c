/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_fd_dup_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:28:41 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 01:42:35 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

static void	help_one(t_info_fd *fd, t_data *data);
static void	help_first(t_info_fd *fd, t_data *data);
static void	help_middle(t_info_fd *fd, t_data *data);
static void	help_last(t_info_fd *fd, t_data *data);

//help_direct_fork
void	helpdf(t_command *cur, t_info_fd *fd, t_data *data)
{
	if (cur->next_command == NULL && fd->index == 0)
		help_one(fd, data);
	if (cur->next_command && fd->index == 0)
		help_first(fd, data);
	if (fd->index > 0 && cur->next_command)
		help_middle(fd, data);
	else if (fd->index > 0 && cur->next_command == NULL)
		help_last(fd, data);
}

static void	help_one(t_info_fd *fd, t_data *data)
{
	if (dup2(fd->oldfd_out, 1) == -1)
		ex_dup2(data);
	if (close(fd->oldfd_out) == -1)
		ex_close_fail(data);
	if (close(fd->oldfd_in) == -1)
		ex_close_fail(data);
}

static void	help_first(t_info_fd *fd, t_data *data)
{
	if (close(fd->oldfd_out) == -1)
		ex_close_fail(data);
	if (dup2(fd->oldfd_in, 0) == -1)
		ex_dup2(data);
	if (close(fd->oldfd_in) == -1)
		ex_close_fail(data);
	if (close(fd->fdpipe[0]) == -1)
		ex_close_fail(data);
	if (dup2(fd->fdpipe[1], 1) == -1)
		ex_dup2(data);
	if (close(fd->fdpipe[1]) == -1)
		ex_close_fail(data);
}

static void	help_middle(t_info_fd *fd, t_data *data)
{
	if (close(fd->oldfd_in) == -1)
		ex_close_fail(data);
	if (close(fd->oldfd_out) == -1)
		ex_close_fail(data);
	if (close(fd->fdpipe[0]) == -1)
		ex_close_fail(data);
	if (dup2(fd->fdpipe[1], 1) == -1)
		ex_dup2(data);
	if (close(fd->fdpipe[1]) == -1)
		ex_close_fail(data);
	if (dup2(fd->fd_0, 0) == -1)
		ex_dup2(data);
	if (close(fd->fd_0) == -1)
		ex_close_fail(data);
}

static void	help_last(t_info_fd *fd, t_data *data)
{
	if (dup2(fd->fd_0, 0) == -1)
		ex_dup2(data);
	if (close(fd->fd_0) == -1)
		ex_close_fail(data);
	if (close(fd->oldfd_in) == -1)
		ex_close_fail(data);
	if (dup2(fd->oldfd_out, 1) == -1)
		ex_dup2(data);
	if (close(fd->oldfd_out) == -1)
		ex_close_fail(data);
}
