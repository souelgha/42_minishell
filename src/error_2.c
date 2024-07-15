/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:57:04 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 10:26:26 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

void	ex_dup2(t_data *data)
{
	perror("dup2()");
	free_data(&data);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	ex_fd(t_command *cu, t_data *data, char **tab)
{
	if (tab)
		get_free(tab);
	if ((*(cu->info))->red)
	{
		perror((*(cu->info))->red);
	}
	free_data(&data);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	ex_pars(t_command ***c, char ***t, t_arg ***p, t_redirect ***i)
{
	if (*t)
		get_free(*t);
	if (*p)
		free_arg_list(*p);
	if (*i)
		free_info_list(*i);
	if (*c)
		free_command_list(c);
	*c = NULL;
}

//free(command, **tab, **parsed **info)
void	ex_mallo_fail(t_data *data, char **t, t_arg **p, t_redirect **i)
{
	ft_fprintf(2, "malloc : corrupted top size\n"
		"Abandon (core dumped)\n");
	if (t)
		get_free(t);
	if (p)
		free_arg_list(p);
	if (i)
		free_info_list(i);
	rl_clear_history();
	free_data(&data);
	exit(EXIT_FAILURE);
}

//free(command, **tab, str, env)
void	ex_malloc(char **tab, char *str, t_data *data)
{
	ft_fprintf(2, "malloc : corrupted top size\n"
		"Abandon (core dumped)\n");
	if (tab)
		get_free(tab);
	if (str)
		free(str);
	rl_clear_history();
	free_data(&data);
	exit(EXIT_FAILURE);
}
