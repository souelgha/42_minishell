/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:48:53 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/19 18:49:27 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

//copy src depuis start, la longueur len-1 dans dest
//garantie to null_terminates la string

void	ft_strcpy_doubleq(char *dest, char *src, int start, int len)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	if (len > 0)
	{
		while ((i < len - 1) && (src[start]))
		{
			if (src[start] == '\\' && src[start + 1] != '\0'
				&& (src[start + 1] == '\\' || src[start + 1] == '\''
					|| src[start + 1] == '\"' || src[start + 1] == '$'))
				start++;
			else if (src[start] == '"')
				start++;
			dest[i] = src[start];
			i++;
			start++;
		}
		dest[i] = '\0';
	}
}

void	ft_strcpy_redir(char *dest, char *src, int start, int len)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	if (len > 0)
	{
		while ((i < len - 1) && (src[start]))
		{
			if (src[start] == '"' || src[start] == '\'')
				start++;
			else
			{
				dest[i] = src[start];
				i++;
				start++;
			}
		}
		dest[i] = '\0';
	}
}

void	ft_strcpy_space(char *dest, char *src, int start, int len)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	if (len > 0)
	{
		while ((i < len - 1) && (src[start]))
		{
			if (src[start] == '\\'
				|| (src[start] == '"' && src[start - 1] == '='))
				start++;
			else if (src[start] == '"' || src[start] == '\'')
				start++;
			else
			{
				dest[i] = src[start];
				i++;
				start++;
			}
		}
		dest[i] = '\0';
	}
}

void	ft_strcpy_quotes(char *dest, char *src, int start, int len)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	if (len > 0)
	{
		while ((i < len - 1) && (src[start]))
		{
			if (src[start] == '\'')
				start++;
			dest[i] = src[start];
			i++;
			start++;
		}
		dest[i] = '\0';
	}
}
