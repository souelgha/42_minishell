/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_arg_reading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:40:57 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 10:06:05 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

void	read_args(t_command **command, t_arg **arg, t_data *data, t_info_fd *fd)
{
	if (!(command))
		return ;
	else if (ft_strncmp((*arg)->str, "cd", 4) == 0)
		data->status = do_cd(arg, data);
	else if (ft_strncmp((*arg)->str, "pwd", 4) == 0)
		data->status = do_pwd(arg, data);
	else if (ft_strncmp((*arg)->str, "export", 7) == 0)
		data->status = do_export(arg, data);
	else if (ft_strncmp((*arg)->str, "unset", 6) == 0)
		data->status = do_unset(arg, data);
	else if (ft_strncmp((*arg)->str, "env", 4) == 0)
		data->status = do_env(data);
	else if (ft_strncmp((*arg)->str, "exit", 5) == 0)
		data->status = do_exit(arg, data, fd);
	else
		return ;
}

//fonction qui nous permet de savoir si la commande est un builtins ou non
int	should_i_fork(t_arg **arg)
{
	if (!arg)
		return (-1);
	if (!(*arg))
		return (-1);
	else if (ft_strncmp((*arg)->str, "cd", 3) == 0)
		return (0);
	else if (ft_strncmp((*arg)->str, "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp((*arg)->str, "export", 7) == 0)
		return (0);
	else if (ft_strncmp((*arg)->str, "unset", 6) == 0)
		return (0);
	else if (ft_strncmp((*arg)->str, "env", 4) == 0)
		return (0);
	else if (ft_strncmp((*arg)->str, "exit", 5) == 0)
		return (0);
	else
		return (-1);
	return (0);
}

//passerelles entre les duplications et l'appel de execve
//verifie si on a bien un commande dans le cas ou on aurais juste un here doc
void	read_args_bis(t_arg **arg, t_data *data)
{
	if (!(*(arg)) || (*arg)->str[0] == '\0')
		ex_no_cmd(arg, data, NULL);
	if (ft_strncmp((*arg)->str, "echo", 5) == 0)
		data->status = do_echo(arg, data);
	exec_command(arg, data);
}
