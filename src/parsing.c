/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:34:11 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 12:20:36 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		pre_par(char ***t, t_command ***c, char **str, t_data *data);
static int		init_begin_list(t_command ***begin_list_arg);
static int		init_parsed_and_info(t_arg ***parsed, t_redirect ***info);

void	parsing(char *str, t_data *data)
{
	char		**command;

	command = parsing_split(str, '|');
	if (!command || init_begin_list(&(data->command)) == -1)
		ex_malloc(command, str, data);
	pre_par(&command, &(data->command), &str, data);
	if (!(data->command))
		return ;
	get_free(command);
}

// t == tab_command c == begin_list_arg
static void	pre_par(char ***t, t_command ***c, char **str, t_data *data)
{
	t_arg		**parsed;
	t_redirect	**info;
	int			i;
	int			status;

	i = 0;
	status = 0;
	while ((*t)[i])
	{
		if (init_parsed_and_info(&parsed, &info) == -1)
			ex_malloc(*t, (*str), data);
		status = start_parsing(parsed, info, &((*t)[i]), data);
		if (status == -1)
			ex_mallo_fail(data, *t, parsed, info);
		if (status == -2)
		{
			ex_pars(c, t, &parsed, &info);
			return ;
		}
		add_node_command(*c, parsed, info);
		if (status == -3)
			ex_fd(NULL, data, *t);
		i++;
	}
}

static int	init_begin_list(t_command ***begin_list_arg)
{
	*begin_list_arg = malloc(sizeof(t_command *));
	if (!begin_list_arg)
		return (-1);
	**begin_list_arg = NULL;
	return (0);
}

static int	init_parsed_and_info(t_arg ***parsed, t_redirect ***info)
{
	*parsed = malloc(sizeof(t_arg *));
	if (!(*parsed))
		return (-1);
	**parsed = NULL;
	*info = malloc(sizeof(t_redirect *));
	if (!(*info))
	{
		free_arg_list(*parsed);
		return (-1);
	}
	**info = NULL;
	return (0);
}
