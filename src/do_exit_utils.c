/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:02:41 by sonouelg          #+#    #+#             */
/*   Updated: 2024/05/21 10:45:33 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

/*****01/05  fichier backup pour deplacer
 * les utils de do_Exit la semaine prochaine*/

int	check_num_arg_exit(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg->str[i] == '-' || arg->str[i] == '+')
		i++;
	if (i > 1)
		return (2);
	while (arg->str[i])
	{
		if (!ft_isdigit(arg->str[i]))
			return (2);
		i++;
	}
	return (0);
}

int	calcul_status_exit(char *str)
{
	int	nb;

	nb = 0;
	nb = ft_atoi(str);
	if (nb == 0 || nb == 256 || nb == -256)
		nb = 0;
	else if (nb < 0 && nb > -256)
		nb += 256;
	else if (nb > 256)
		nb = nb % 256;
	else if (nb < -256)
		nb = 256 + nb % 256;
	printf("nb=<%d>\n", nb);
	printf("exit\n");
	return (nb);
}

void	exit_tasks(t_data *data)
{
	free_data(&data);
	rl_clear_history();
	exit(data->status);
}
