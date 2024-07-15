/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_utils_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:41:10 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 17:08:28 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	final_step(char **value, char **splitab);
static char	**get_pipe_tab(char **value, t_data *data, char **str, int clic);
static void	add_pipe(char ***split_pipe_value, int clic);

void	check_value(char **value, t_data *data, char **str)
{
	int		clic;
	char	**split_pipe_value;

	clic = 0;
	if ((*value)[ft_strlen(*value) - 1] == '|')
		clic = 1;
	split_pipe_value = get_pipe_tab(value, data, str, clic);
	if (!split_pipe_value)
		return ;
	add_pipe(&split_pipe_value, clic);
	final_step(value, split_pipe_value);
	get_free(split_pipe_value);
}

static void	final_step(char **value, char **splitab)
{
	char	*result;
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	result = NULL;
	free(*value);
	*value = NULL;
	while (splitab[i + 1])
	{
		if (!result)
			result = ft_strjoin(splitab[i], splitab[i + 1]);
		else
		{
			tmp = ft_strjoin(result, splitab[i + 1]);
			free(result);
			result = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	*value = ft_strdup(result);
	free(result);
}

static char	**get_pipe_tab(char **value, t_data *data, char **str, int clic)
{
	char	**split_pipe_value;

	split_pipe_value = parsing_split(*value, '|');
	if (!split_pipe_value)
		free_all_object(*str, *value, NULL, data);
	if (split_pipe_value[1] == NULL && clic == 0)
	{
		get_free(split_pipe_value);
		return (NULL);
	}
	return (split_pipe_value);
}

static void	add_pipe(char ***split_pipe_value, int clic)
{
	int		i;
	char	*result;

	i = 0;
	if (clic == 0)
	{
		while ((*split_pipe_value)[i + 1])
		{
			result = ft_strjoin((*split_pipe_value)[i], "\"|\"");
			free((*split_pipe_value[i]));
			(*split_pipe_value)[i] = ft_strdup(result);
			free(result);
			i++;
		}
		return ;
	}
	while ((*split_pipe_value)[i])
	{
		result = ft_strjoin((*split_pipe_value)[i], "\"|\"");
		free((*split_pipe_value)[i]);
		(*split_pipe_value)[i] = ft_strdup(result);
		free(result);
		i++;
	}
}
