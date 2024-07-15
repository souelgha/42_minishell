/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:13:10 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 12:26:31 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

static char	**help_fill_in(char **tmp, char **last_part, char **str);

//fonction qui copie le nom de la variable demander
//créer une copie qui doit etre free
char	*var_env(char **str, int *index, t_data *data)
{
	int		size;
	int		start;
	char	*name_var;

	size = 0;
	start = *index;
	while ((*str)[start] && (ft_isalnum((*str)[start])
		|| (*str)[start] == '_'))
	{
		size += 1;
		start++;
	}
	name_var = malloc((size + 1) * sizeof(char));
	if (!name_var)
		ex_malloc(NULL, (*str), data);
	start = 0;
	while (start < size)
	{
		name_var[start] = (*str)[*index];
		(*index)++;
		start++;
	}
	(*index) -= start;
	name_var[start] = '\0';
	return (name_var);
}

//fonction qui permet de rassembler les morceau de notre str
//first_part->to_put_in->last_part (si elle existe)
//protected
void	fill_in(char **str, char *to_put_in, int *index, t_data *data)
{
	char	*first_part;
	char	*last_part;
	char	*tmp;

	first_part = get_first_part(str, *index, data);
	last_part = get_last_part(str, *index, data, first_part);
	tmp = ft_strjoin(first_part, to_put_in);
	free(first_part);
	if (!tmp)
		free_all_object((*str), to_put_in, last_part, data);
	(*index) = ft_strlen(tmp);
	free((*str));
	str = help_fill_in(&tmp, &last_part, str);
	if (!(*str))
		free_all_object((*str), to_put_in, last_part, data);
}

static char	**help_fill_in(char **tmp, char **last_part, char **str)
{
	if (*last_part)
		*str = ft_strjoin(*tmp, *last_part);
	else
		*str = ft_strdup(*tmp);
	if (*last_part)
		free(*last_part);
	free(*tmp);
	return (str);
}

int	help_interpret_dollar(char **str, t_data *data, int *index)
{
	char	*name_var;
	char	*value;

	name_var = var_env(str, index, data);
	value = find_var(name_var, data);
	if (!value)
	{
		clean_str_after_dollar(str, data, index);
		free (name_var);
		return (0);
	}
	free (name_var);
	check_value(&value, data, str);
	fill_in(str, value, index, data);
	free(value);
	return (0);
}
