/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:41:06 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 10:37:48 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

t_env	*add_node(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

//protected
void	get_nodded(char *var_1, char *value_1, t_data *data)
{
	t_env	*tmp;

	if (!(*(data->env)))
		env_empty(var_1, value_1, data);
	else
	{
		tmp = *(data->env);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add_node();
		if (!tmp->next)
		{
			free(var_1);
			ex_malloc(NULL, value_1, data);
		}
		tmp = tmp->next;
		cpy_var_value(var_1, value_1, data, tmp);
	}
}

//protected
//si c'est le premier node de la chaine
void	env_empty(char *var_1, char *value_1, t_data *data)
{
	t_env	*tmp;

	*(data->env) = add_node();
	if (!(*(data->env)))
	{
		free(var_1);
		ex_malloc(NULL, value_1, data);
	}
	tmp = *(data->env);
	cpy_var_value(var_1, value_1, data, tmp);
}

//go copier les valeurs dans la chaine
void	cpy_var_value(char *var_1, char *value_1, t_data *data, t_env *tmp)
{
	tmp->var = ft_strdup(var_1);
	if (!tmp->var)
	{
		free(var_1);
		ex_malloc(NULL, value_1, data);
	}
	tmp->value = ft_strdup(value_1);
	if (!tmp->value)
	{
		free(value_1);
		ex_malloc(NULL, var_1, data);
	}
	tmp->next = NULL;
}
