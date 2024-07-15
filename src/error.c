/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:53:25 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 14:09:55 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

int	ex_no_cmd(t_arg **current, t_data *data, t_exec *info)
{
	int	status;

	status = 127;
	if ((*current))
	{
		if ((*current)->str)
			ft_fprintf(2, "minishell: %s: command not "
				"found\n", (*current)->str);
	}
	if (data)
		free_data(&data);
	if (info)
	{
		if (info->path_name)
			free(info->path_name);
	}
	rl_clear_history();
	exit(status);
}

int	exit_execve(t_arg **current, t_data *data, t_exec *info)
{
	int	x;

	if (errno == ENOEXEC)
	{
		ft_fprintf(2, "command not found\n");
		x = 127;
	}
	else
	{
		perror((*current)->str);
		x = 126;
	}
	if (data)
		free_data(&data);
	if (info->path_name)
		free(info->path_name);
	if (info->path_envp)
		get_free(info->path_envp);
	rl_clear_history();
	exit(x);
}

void	ex_pip(char *str)
{
	rl_clear_history();
	exit_error(str);
}

void	ex_pid(char *str, int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	rl_clear_history();
	exit_error(str);
}

void	exit_error(char	*str)
{
	perror(str);
	rl_clear_history();
	exit(EXIT_FAILURE);
}
