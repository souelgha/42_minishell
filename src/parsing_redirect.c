/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:34:11 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 12:09:32 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 17

static int	clic_1(char **str, int *index, int clic);
static int	clic_0(char **str, int *index);

int	redirection_parsing(t_redirect **info, char **str, int *index, t_data *data)
{
	int			size;
	int			start;
	int			find_token;
	t_redirect	*current;

	size = 0;
	find_token = *index;
	if (token_management((*str), index, data) == -1)
		return (-2);
	size = get_redir_size(str, index, &start);
	current = add_node_info(info, size + 1);
	if (!current)
		return (-1);
	current->token = get_token((*str), find_token);
	if (current->token == 3)
		return (redirection_here_doc(current, str, index, start));
	if (current->token == -1)
		return (-2);
	ft_strcpy_redir(current->red, (*str), start, size + 1);
	if ((*str)[*index] == '\0')
		return (1);
	return (0);
}

int	get_redir_size(char **str, int *index, int *start)
{
	int	clic;
	int	size;

	size = 0;
	clic = 0;
	while ((*str)[*index] && (((*str)[*index] == ' '
		|| (*str)[*index] == '\t' || (*str)[*index] == '\n')))
		(*index)++;
	if ((*str)[*index] == '"')
	{
		(*index)++;
		clic = 1;
	}
	*start = *index;
	if (clic == 1)
		size = clic_1(str, index, clic);
	else
		size = clic_0(str, index);
	return (size);
}

static int	clic_0(char **str, int *index)
{
	int	size;

	size = 0;
	while ((*str)[*index] && ((*str)[*index] != ' '
		&& (*str)[*index] != '\t' && (*str)[*index] != '\n'))
	{
		if ((*str)[*index] == '"' || (*str)[*index] == '\'')
			(*index)++;
		else
		{
			size++;
			(*index)++;
		}
	}
	return (size);
}

static int	clic_1(char **str, int *index, int clic)
{
	int	size;

	size = 0;
	while (clic == 1)
	{
		while ((*str)[*index] && (*str)[*index] != '"')
		{
			size++;
			(*index)++;
		}
		(*index)++;
		if ((*str)[*index] == '"')
		{
			clic = 1;
			(*index)++;
		}
		else
			clic = 0;
	}
	return (size);
}
