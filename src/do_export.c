/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:54:12 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 01:55:19 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

static void	export_no_arg(t_data *data);

int	do_export(t_arg **arg, t_data *data)
{
	int		status;

	status = 0;
	if ((*arg)->next)
		status = do_export_arg(arg, data);
	else
		export_no_arg(data);
	return (status);
}

/***affichage export commande sans argument ***/

void	export_no_arg(t_data *data)
{
	t_env	*tmp_env;

	tmp_env = *(data->env);
	while (tmp_env)
	{
		if (!tmp_env->value)
		{
			if (ft_strchr(tmp_env->var, '='))
				ft_printf("declare -x %s\"\"\n", tmp_env->var);
			else
				ft_printf("declare -x %s\n", tmp_env->var);
		}
		else if (ft_strncmp(tmp_env->var, "OLDPWD", 7) == 0)
			ft_printf("declare -x %s\n", tmp_env->var);
		else if (ft_strncmp(tmp_env->var, "_=", 2) != 0)
			ft_printf("declare -x %s\"%s\"\n", tmp_env->var, tmp_env->value);
		tmp_env = tmp_env->next;
	}
}
