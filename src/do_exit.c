/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:54:12 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 17:56:27 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_num_arg_exit(t_arg *arg);
static void	exit_no_arg(t_data *data, t_info_fd *fd, int b);
static int	exit_stat(t_arg **arg, t_data *data, t_info_fd *fd);
static int	calcul_status_exit(char *str);

int	do_exit(t_arg **arg, t_data *data, t_info_fd *fd)
{
	int	bool;

	bool = fd->bool;
	if (!(*arg)->next)
		exit_no_arg(data, fd, bool);
	else
	{
		data->status = check_num_arg_exit((*arg)->next);
		if (data->status == 2)
		{
			fd->bool = 2;
			exit_stat(arg, data, fd);
		}
		else if (data->status == 0 && ((*arg)->next->next))
		{
			fd->bool = 1;
			return (exit_stat(arg, data, fd));
		}
		data->status = calcul_status_exit((*arg)->next->str);
		exit_no_arg(data, fd, bool);
	}
	return (0);
}

static int	calcul_status_exit(char *str)
{
	int	nb;

	nb = 0;
	nb = ft_atol(str);
	if (nb == 0 || nb == 256 || nb == -256)
		nb = 0;
	else if (nb < 0 && nb > -256)
		nb += 256;
	else if (nb > 256)
		nb = nb % 256;
	else if (nb < -256)
		nb = 256 + nb % 256;
	return (nb);
}

static int	check_num_arg_exit(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg->str[i] == '-' || arg->str[i] == '+')
		i++;
	if (i > 1)
		return (2);
	while (arg->str[i])
	{
		if (!(ft_isdigit(arg->str[i])))
			return (2);
		i++;
	}
	if ((ft_strncmp(arg->str, "9223372036854775807", 20) > 0)
		|| ((ft_strncmp(arg->str, "9223372036854775807", 20) == -12
				&& ft_strncmp(arg->str, "-9223372036854775808", 21) > 0)))
		return (2);
	return (0);
}

static void	exit_no_arg(t_data *data, t_info_fd *fd, int b)
{
	int	status;

	status = data->status;
	if (b != 1)
	{
		if (fd->oldfd_in != -1)
		{
			if (close(fd->oldfd_in) == -1)
				ex_close_fail(data);
		}
		if (fd->oldfd_out != -1)
		{
			if (close(fd->oldfd_out) == -1)
				ex_close_fail(data);
		}
		if (b != 0)
			printf("exit\n");
	}
	rl_clear_history();
	free_data(&data);
	exit(status);
}

static int	exit_stat(t_arg **arg, t_data *data, t_info_fd *fd)
{
	if (fd->bool == 2)
	{
		printf("exit\n");
		ft_fprintf(2, "exit : %s: numeric argument required\n",
			(*arg)->next->str);
		exit_no_arg(data, fd, 0);
	}
	if (fd->bool == 1)
	{
		printf("exit\n");
		ft_fprintf(2, "exit : too many arguments\n");
		data->status = 1;
		return (data->status);
	}
	return (0);
}
