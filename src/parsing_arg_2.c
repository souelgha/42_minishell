/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:17:17 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/19 12:50:03 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_of_2(char *str, int *index);

int	double_quotes_parsing(t_arg **parsed, char *str, int *index)
{
	int		start;
	int		size;
	t_arg	*current;

	size = 0;
	*index += 1;
	start = *index;
	size = size_of_2(str, index);
	if (size == 0)
		return (2);
	current = add_node_arg(parsed, size + 1);
	if (!current)
		return (-1);
	ft_strcpy_doubleq(current->str, str, start, size + 1);
	if (str[*index] == '\0')
		return (1);
	return (3);
}

static int	size_of_2(char *str, int *index)
{
	int	size;

	size = 0;
	while (str[*index] != '\0')
	{
		if (str[*index] == '\\' && str[*index + 1] != '\0'
			&& (str[*index + 1] == '\\' || str[*index + 1] == '\''
				|| str[*index + 1] == '"' || str[*index + 1] == '$'))
			(*index)++;
		if (str[*index] == '"')
			break ;
		size++;
		(*index)++;
	}
	return (size);
}
