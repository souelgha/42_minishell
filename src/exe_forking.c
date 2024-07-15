/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_forking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:24:02 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 10:58:06 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	son(t_command **cmd, t_command *cur, t_info_fd *fd, t_data *data);
static void	got_more_cmd(t_info_fd *fd, t_data *data);

void	forkg(t_command **cmd, t_command *cur, t_info_fd *fd, t_data *data)
{
	pid_t		pid;
	t_redirect	**redir;
	t_redirect	*tmp;

	redir = cur->info;
	tmp = (*redir);
	ignore_sig();
	pid = fork();
	if (pid == -1)
		ex_pid("pid", NULL);
	if (pid == 0)
		son(cmd, cur, fd, data);
	cur->pid = pid;
	whd(tmp, fd, data);
	if (cur->next_command)
		got_more_cmd(fd, data);
	if (fd->index > 0 && cur->next_command == NULL)
	{
		if (close(fd->fd_0) == -1)
			ex_close_fail(data);
	}
	fd->index++;
}

static void	son(t_command **cmd, t_command *cur, t_info_fd *fd, t_data *data)
{
	int	should_i;

	signal_research_fork();
	helpdf(cur, fd, data);
	do_redirect(cur, data);
	should_i = should_i_fork(cur->arg);
	if (should_i != -1)
	{
		fd->bool = 1;
		read_args(cmd, cur->arg, data, fd);
		ex_cmd(data);
	}
	rl_clear_history();
	read_args_bis(cur->arg, data);
}

static void	got_more_cmd(t_info_fd *fd, t_data *data)
{
	if (fd->index > 0)
	{
		if (close(fd->fd_0) == -1)
			ex_close_fail(data);
	}
	fd->fd_0 = fd->fdpipe[0];
	if (close(fd->fdpipe[1]) == -1)
		ex_close_fail(data);
}
