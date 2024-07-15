/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirect_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:59:31 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/20 15:24:44 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	clic_equal_0(char **str, int i);

int	get_size_redir(char **str, int *start)
{
	int	size;
	int	clic;
	int	i;

	size = 0;
	clic = get_clic(str, start);
	i = (*start);
	if (clic == 1)
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
			size = clic_equal_0(str, i);
		else
		{
			while ((*str)[i] && (*str)[i] != '\'' && (*str)[i] != '"')
			{
				i++;
				(size++);
			}
		}
	}
	else
	{
		size = clic_equal_0(str, i);
	}
	return (size);
}

static int	clic_equal_0(char **str, int i)
{
	int	size;

	size = 0;
	while ((*str)[i] && (((*str)[i] != ' '
		&& (*str)[i] != '\t' && (*str)[i] != '\n')))
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
			i++;
		else
		{
			i++;
			(size++);
		}
	}
	return (size);
}

int	get_clic(char **str, int *start)
{
	int	clic;

	clic = 0;
	if ((*str)[*start - 1] == '\'' || (*str)[*start - 1] == '"')
		return (1);
	if ((*str)[*start] == ' ')
		(*start) += 1;
	if ((*str)[*start] == '\'' || (*str)[*start] == '"')
	{
		(*start) += 1;
		clic = 1;
	}
	return (clic);
}
