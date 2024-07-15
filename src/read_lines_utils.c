/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:39:01 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 11:50:27 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

int	check_quotes(char **str, int *start, t_data *data)
{
	char	*tmp;

	tmp = NULL;
	while ((*str)[*start])
	{
		if ((*str)[*start] == '\'')
			return (1);
		(*start)++;
	}
	tmp = ft_strjoin(*str, "\n");
	if (!tmp)
		ex_malloc(NULL, (*str), data);
	free(*str);
	*str = NULL;
	*str = ft_strdup(tmp);
	if (!(*str))
		ex_malloc(NULL, tmp, data);
	free(tmp);
	return (0);
}

int	found_dollar(char **str, int *start)
{
	if ((*str)[*start + 1] == '$')
		return (0);
	else
	{
		while ((*str)[*start])
		{
			if ((*str)[*start] == '\"')
				return (1);
			else if (!(ft_isalnum((*str)[*start]) != 0
				|| ((*str)[*start] == '_')))
				return (0);
			(*start)++;
		}
	}
	return (0);
}

int	check_double_quotes(char **str, int *start, t_data *data)
{
	char	*tmp;

	tmp = NULL;
	while ((*str)[*start])
	{
		if ((*str)[*start] == '$' && found_dollar(str, start) == 1)
			return (1);
		if ((*str)[*start] == '"')
			return (1);
		if ((*str)[*start] == '\\')
			(*start)++;
		(*start)++;
	}
	tmp = ft_strjoin((*str), "\n");
	if (!tmp)
		ex_malloc(NULL, (*str), data);
	free(*str);
	*str = NULL;
	*str = ft_strdup(tmp);
	if (!str)
		ex_malloc(NULL, tmp, data);
	free(tmp);
	return (0);
}

void	help_tmp_null(char *prompt_line, t_data *data)
{
	free(prompt_line);
	rl_clear_history();
	free_data(&data);
	ft_fprintf(1, "minishell : exit\n");
	exit(EXIT_SUCCESS);
}
