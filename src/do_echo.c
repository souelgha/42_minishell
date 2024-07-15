/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:54:12 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 18:00:38 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

int	do_echo(t_arg **arg, t_data *data)
{
	t_arg	*tmp;

	if (!(*arg)->next)
		echo_no_arg(data);
	tmp = (*arg)->next;
	if (ft_strncmp(tmp->str, "-n", 2) == 0
		&& (check_n_char(tmp->str, 'n')) == 0)
		echo_arg(data, tmp);
	else
	{
		while (tmp)
		{
			printf("%s", tmp->str);
			if (tmp->next)
				printf(" ");
			tmp = tmp->next;
		}
		printf("\n");
	}
	rl_clear_history();
	free_data(&data);
	exit(EXIT_SUCCESS);
}

//print un retour a la ligne
void	echo_no_arg(t_data *data)
{
	printf("\n");
	free_data(&data);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

/*** arg dont -n *****/
void	echo_arg(t_data *data, t_arg *tmp)
{
	while (tmp && (ft_strncmp(tmp->str, "-n", 2) == 0)
		&& (check_n_char(tmp->str, 'n')) == 0)
		tmp = tmp->next;
	if (!tmp)
	{
		rl_clear_history();
		free_data(&data);
		exit(EXIT_SUCCESS);
	}
	while (tmp)
	{
		printf("%s", tmp->str);
		if (tmp->next)
			printf(" ");
		tmp = tmp->next;
	}
	rl_clear_history();
	free_data(&data);
	exit(EXIT_SUCCESS);
}

/***** check de tous les chars de "-n" s ils sont egaux a 'n'****/
int	check_n_char(char *str, char n)
{
	size_t	i;

	i = 1;
	while (str[i] && str[i] == n)
		i++;
	if (i == ft_strlen(str))
		return (0);
	return (1);
}
