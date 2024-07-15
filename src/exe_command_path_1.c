/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command_path_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:55:25 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 10:06:09 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

static char	**get_path_help(t_data *data, char *path_name);

//rend un tableau avec tout les differents chemin de la variable PATH
char	**get_path_envp(t_data *data)
{
	t_env	*tmp;
	char	*path_name;

	tmp = *(data->env);
	path_name = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PATH=", 5) == 0)
		{
			path_name = ft_strdup(tmp->value);
			if (!path_name)
				ex_malloc(NULL, NULL, data);
			break ;
		}
		tmp = tmp->next;
	}
	if (path_name != NULL)
		return (get_path_help(data, path_name));
	return (NULL);
}

static char	**get_path_help(t_data *data, char *path_name)
{
	char	**final_tab;

	final_tab = ft_split(path_name, ':');
	if (!final_tab)
		ex_malloc(NULL, path_name, data);
	free(path_name);
	return (final_tab);
}
