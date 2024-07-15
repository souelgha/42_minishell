/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:54:21 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 16:54:08 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//protected
//1 : creation de l'environnement a partir de l'environnement recue
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		ex_malloc(NULL, NULL, NULL);
	init_data(&data);
	data->env = malloc(sizeof(t_env *));
	if (!(data->env))
		ex_malloc(NULL, NULL, data);
	*(data->env) = NULL;
	env_cpy(envp, data, 0, 0);
	return (loop_minishell(data));
}

void	init_data(t_data **data)
{
	(*data)->command = NULL;
	(*data)->env = NULL;
	(*data)->ex_g_fd = -1;
	(*data)->status = 0;
}

void	free_data(t_data **data)
{
	if (*data)
	{
		if ((*data)->command)
		{
			free_command_list(&((*data)->command));
			(*data)->command = NULL;
		}
		if ((*data)->env)
		{
			free_env((*data)->env);
			(*data)->env = NULL;
		}
		free(*data);
		*data = NULL;
	}
}
