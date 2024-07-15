/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:31:12 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 01:10:18 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

//fonction qui va trouver la fin du nom de la variable 
//et copier jusqu'a la fin de la string (sans regarder si 
//il y a d'autre caractère $)
//la copie doit etre free
//protected
char	*get_last_part(char **str, int start_to, t_data *data, char *alloc_str)
{
	int		start;
	char	*last_part;

	while ((*str)[start_to] && (ft_isalnum((*str)[start_to])
		|| (*str)[start_to] == '_'))
		start_to++;
	if ((*str)[start_to] == '\0' || ((*str)[start_to - 1] == '$' &&
		(*str)[start_to] == '?' && (*str)[start_to + 1] == '\0'))
		return (NULL);
	if ((*str)[start_to - 1] == '$' && (*str)[start_to] == '?')
		start_to++;
	start = start_to;
	last_part = help_last_part(str, start, data, alloc_str);
	return (last_part);
}

//protected
char	*help_last_part(char **str, int start, t_data *data, char *alloc_str)
{
	char	*last_part;
	int		size;
	int		i;

	size = 0;
	i = start;
	while ((*str)[i])
	{
		size++;
		i++;
	}
	last_part = malloc((size + 1) * sizeof(char));
	if (!last_part)
		ex_malloc(NULL, alloc_str, data);
	size = 0;
	while ((*str)[start])
	{
		last_part[size] = (*str)[start];
		size++;
		start++;
	}
	last_part[size] = '\0';
	return (last_part);
}

//fonction qui va recopier la string jus'quau caractère $
//until = $
//renvoie une copie du debut de la chaine
//la copie doit etre free
//protected
char	*get_first_part(char **str, int until, t_data *data)
{
	int		i;
	char	*first_part;

	i = 0;
	if (until == 0)
		return (NULL);
	first_part = malloc((until) * sizeof(char));
	if (!first_part)
		ex_malloc(NULL, NULL, data);
	while (i < until - 1)
	{
		first_part[i] = (*str)[i];
		i++;
	}
	first_part[i] = '\0';
	return (first_part);
}

//fonction qui nous permet de trouver la valeur associé au nom de notre variable
//renvoie une copie de cette valeur qui doit etre free;
//protected
char	*find_var(char *name_var, t_data *data)
{
	t_env	*tmp;
	char	*value;

	if (name_var[0] == '\0')
		return (NULL);
	tmp = *(data->env);
	while (tmp)
	{
		if (((ft_strlen(tmp->var) - 1) == ft_strlen(name_var))
			&& (ft_strncmp(tmp->var, name_var, ft_strlen(name_var)) == 0))
		{
			if (tmp->value != NULL)
				value = ft_strdup(tmp->value);
			else
				value = ft_strdup("");
			if (!value)
				ex_malloc(NULL, NULL, data);
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*replace(int status)
{
	char	*to_put_in;

	to_put_in = ft_itoa(status);
	return (to_put_in);
}
