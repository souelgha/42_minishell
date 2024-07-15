/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:34:11 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 15:17:50 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_of(char *str, int *index);

//PROTECTED 
int	space_parsing(t_arg	**parsed, char *str, int *index)
{
	int		size;
	int		start;
	t_arg	*current;

	start = *index;
	size = size_of(str, index);
	current = add_node_arg(parsed, size + 1);
	if (!current)
		return (-1);
	ft_strcpy_space(current->str, str, start, size + 1);
	if (str[*index] == '\0')
		return (1);
	return (3);
}

static int	size_of(char *str, int *index)
{
	int		size;

	size = 0;
	while (str[*index] && (str[*index] != ' ' && str[*index] != '\t'))
	{
		if (str[*index] == '"' || str[*index] == '\'')
			break ;
		else if (str[*index] == '\\')
			(*index)++;
		else if (str[*index] == '=' && str[*index + 1] == '"')
		{
			get_full_size_of_arg(str, index, &size);
			break ;
		}
		else if (str[*index] == '<' || str[*index] == '>')
			break ;
		else
		{
			size++;
			(*index)++;
		}
	}
	return (size);
}

//ok
void	get_full_size_of_arg(char *str, int *start, int *size)
{
	(*start)++;
	(*size)++;
	(*start)++;
	while (str[*start] != '"')
	{
		(*start)++;
		(*size)++;
	}
	(*start)++;
}

int	quotes_parsing(t_arg **parsed, char *str, int *index)
{
	int		start;
	int		size;
	t_arg	*current;

	size = 0;
	*index += 1;
	start = *index;
	while (str[*index] != '\0')
	{
		if (str[*index] == '\'')
			break ;
		size++;
		(*index)++;
	}
	if (size == 0)
		return (2);
	current = add_node_arg(parsed, size + 1);
	if (!current)
		return (-1);
	ft_strcpy_quotes(current->str, str, start, size + 1);
	if (str[*index] == '\0')
		return (1);
	return (3);
}
