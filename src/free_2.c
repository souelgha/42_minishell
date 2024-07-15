/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:19:18 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 11:38:59 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

/*** free des variables du node ****/
void	free_char(char *var, char *value)
{
	free(var);
	free(value);
}

void	get_free(char **splitted)
{
	int	i;

	i = 0;
	if (splitted)
	{
		while (splitted[i])
		{
			free(splitted[i]);
			i++;
		}
	}
	if (splitted)
		free(splitted);
	splitted = NULL;
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		*env = tmp->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
		tmp = *env;
	}
	if (env)
		free(env);
	env = NULL;
}

void	free_all_object(char *str, char *str1, char *str2, t_data *data)
{
	if (str)
		free(str);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (data)
		free_data(&data);
	ex_malloc(NULL, NULL, NULL);
}
