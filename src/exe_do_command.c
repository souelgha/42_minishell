/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_do_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:06:16 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 10:59:19 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 17

/********fonction pour choix de type de commande *****/
void	direct_command(t_data *data)
{
	t_command	*current_cmd;
	t_info_fd	fd;
	int			should_i;

	init_info_fd(&fd);
	current_cmd = *(data->command);
	while (current_cmd)
	{
		if (current_cmd->next_command)
		{
			if (pipe(fd.fdpipe) == -1)
				ex_pip("pipe");
		}
		should_i = should_i_fork(current_cmd->arg);
		if (fd.index > 0 || (should_i != -1
				&& current_cmd->next_command) || should_i == -1)
			forkg(data->command, current_cmd, &fd, data);
		else
			no_fork(data->command, data, current_cmd, &fd);
		current_cmd = current_cmd->next_command;
	}
	if (fd.index > 1 || should_i == -1)
		pid_waiting(data->command, data);
	if (close(fd.oldfd_in) == -1 || close(fd.oldfd_out) == -1)
		ex_close_fail(data);
}

//utilisation des builtins lorsqu'ils sont appele en solo
void	no_fork(t_command **cmd, t_data *d, t_command *cur_cmd, t_info_fd *fd)
{
	do_redirect(cur_cmd, d);
	read_args(cmd, cur_cmd->arg, d, fd);
	fd->index++;
	if (dup2(fd->oldfd_in, 0) == -1)
		ex_dup2(d);
	if (dup2(fd->oldfd_out, 1) == -1)
		ex_dup2(d);
}

void	pid_waiting(t_command **command, t_data *data)
{
	t_command	*tmp;

	tmp = (*command);
	while (tmp)
	{
		if (tmp->next_command == NULL)
		{
			waitpid(tmp->pid, &(data->status), 0);
			if (data->status == 131)
			{
				ft_fprintf(2, "Quitter (core dumped)\n");
				return ;
			}
			if (data->status == 2)
			{
				data->status = 130;
				return ;
			}
			if (WIFEXITED(data->status))
				data->status = WEXITSTATUS(data->status);
		}
		else
			waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next_command;
	}
}
