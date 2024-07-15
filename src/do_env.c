/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:49:45 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/20 23:54:42 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

/***** check si PATH existe ****/
int	check_var_path_exist(t_data *data)
{
	t_env	*tmp;
	int		path;

	path = 0;
	tmp = *(data->env);
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PATH=", 5) == 0 && tmp->value != NULL)
			path = 1;
		tmp = tmp->next;
	}
	return (path);
}

/**** fonction qui compte le nombre de variable d env*/
int	check_env_isempty(t_data *data)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *(data->env);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	do_env(t_data *data)
{
	t_env	*tmp;

	tmp = *(data->env);
	if (((check_env_isempty(data) >= 4) && (check_env_isempty(data) <= 8)
			&& (!check_var_path_exist(data))) || (check_var_path_exist(data)))
	{
		while (tmp)
		{
			if (tmp->value == NULL && (ft_strchr(tmp->var, '=')))
				printf("%s\n", tmp->var);
			else if ((tmp->value) && (ft_strchr(tmp->var, '=')))
				printf("%s%s\n", tmp->var, tmp->value);
			tmp = tmp->next;
		}
		return (0);
	}
	else if (!check_var_path_exist(data))
	{
		ft_fprintf(2, "env: No such file or directory\n");
		return (127);
	}
	return (0);
}
