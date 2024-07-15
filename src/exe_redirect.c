/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:37:06 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 01:45:58 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

static void	h_1(t_command *cur, t_redirect *red, t_data *data);
static void	h_2(t_command *cur, t_redirect *red, t_data *data);
static void	help_3(t_redirect *red, t_data *data);
static void	get_prio_fd(t_command *curr_cmd, t_data *data);

int	do_redirect(t_command *cur_cmd, t_data *data)
{
	t_redirect	*redir;
	t_redirect	**begin_list;

	begin_list = cur_cmd->info;
	redir = (*begin_list);
	while (redir)
	{
		if (redir->token == 1)
			h_1(cur_cmd, redir, data);
		else if (redir->token == 2)
			h_2(cur_cmd, redir, data);
		else if (redir->token == 3)
			help_3(redir, data);
		else if (redir->token == 4)
		{
			cur_cmd->fd_prio.fd_redirect_in = open(redir->red, O_RDONLY);
			if (cur_cmd->fd_prio.fd_redirect_in < 0)
				ex_fd(cur_cmd, data, NULL);
		}
		redir = redir->next;
	}
	get_prio_fd(cur_cmd, data);
	return (0);
}

static void	help_3(t_redirect *red, t_data *data)
{
	char		*joined;
	int			fd;

	joined = ft_strjoin("/tmp/", red->red);
	if (!joined)
		ex_malloc(NULL, NULL, data);
	fd = open(joined, O_RDONLY);
	free(joined);
	if (fd < 0)
		ex_fd(NULL, data, NULL);
	if (dup2(fd, 0) == -1)
		ex_dup2(data);
	if (close(fd) == -1)
		ex_close_fail(data);
}

//cur = current command, red = redirect
static void	h_1(t_command *cur, t_redirect *red, t_data *data)
{
	cur->fd_prio.fd_redirect_out = open(red->red, O_WRONLY
			| O_APPEND | O_CREAT, 0755);
	if (cur->fd_prio.fd_redirect_out < 0)
		ex_fd(cur, data, NULL);
}

static void	h_2(t_command *cur, t_redirect *red, t_data *data)
{
	cur->fd_prio.fd_redirect_out = open(red->red, O_CREAT
			| O_TRUNC | O_WRONLY, 0666);
	if (cur->fd_prio.fd_redirect_out < 0)
		ex_fd(cur, data, NULL);
}

static void	get_prio_fd(t_command *curr_cmd, t_data *data)
{
	if (curr_cmd->fd_prio.fd_redirect_in != -1)
	{
		if (dup2(curr_cmd->fd_prio.fd_redirect_in, 0) == -1)
			ex_dup2(data);
		if (close(curr_cmd->fd_prio.fd_redirect_in) == -1)
			ex_close_fail(data);
	}
	if (curr_cmd->fd_prio.fd_redirect_out != -1)
	{
		if (dup2(curr_cmd->fd_prio.fd_redirect_out, 1) == -1)
			ex_dup2(data);
		if (close(curr_cmd->fd_prio.fd_redirect_out) == -1)
			ex_close_fail(data);
	}
}
