/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:15:27 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/20 12:22:39 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pass_q_dq(const char *s, int *index)
{
	if (s[*index] == '"')
	{
		(*index)++;
		while (s[*index] && s[*index] != '"')
			(*index)++;
	}
	else if (s[*index] == '\'')
	{
		(*index)++;
		while (s[*index] && s[*index] != '\'')
			(*index)++;
	}
	if (s[*index] == '\0')
		return (1);
	return (0);
}

static int	ft_tab(const char *s, char c)
{
	int	count_sep;
	int	clic;
	int	index;

	count_sep = 0;
	clic = 1;
	index = 0;
	while (s[index])
	{
		if (s[index] == '"' || s[index] == '\'')
		{
			if (pass_q_dq(s, &index) == 1)
				break ;
		}
		else if (s[index] == c)
			clic = 1;
		else if (s[index] != c && clic == 1)
		{
			count_sep++;
			clic = 0;
		}
		index++;
	}
	return (count_sep);
}

static void	ft_cpy_w(char const *s, int start, int end, char *dest)
{
	int	i;

	i = 0;
	while (start < end)
	{
		dest[i] = s[start];
		start++;
		i++;
	}
	dest[i] = '\0';
}

static char	*ft_mal_cpy(char const *s, char c, int *start)
{
	char	*str;
	int		end;

	end = *start;
	while (s[end] != '\0')
	{
		if (s[end] == '"' || s[end] == '\'')
		{
			if (pass_q_dq(s, &end) == 1)
				break ;
		}
		else if (s[end] == c)
			break ;
		end++;
	}
	str = malloc(((end - (*start)) + 1) * sizeof(char));
	ft_cpy_w(s, *start, end, str);
	*start = end;
	return (str);
}

char	**parsing_split(char const *s, char c)
{
	char	**tab;
	int		index;
	int		i;

	if (!(s))
		return (NULL);
	index = 0;
	tab = malloc((ft_tab(s, c) + 2) * sizeof(char *));
	if (!(tab))
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[index] = ft_mal_cpy(s, c, &i);
			index++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	tab[index] = NULL;
	return (tab);
}
