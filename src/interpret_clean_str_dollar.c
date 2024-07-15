/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_clean_str_dollar.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:28:45 by sonouelg          #+#    #+#             */
/*   Updated: 2024/05/21 10:09:08 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

static char	*get_lp_dollar(char **str, int st_to, t_data *data, char *al_str);

//modification marianne 29/04 ; ajout de env, 
//et alloc_char pour pouvoir free si malloc fail
/*******26/04 modification de indice de last a i -1 car
//bug avec inter du 2e $*/
void	clean_str_after_dollar(char **str, t_data *data, int *index)
{
	char	*first_part;
	char	*last_part;

	first_part = get_first_part_clear(str, *index -1, data);
	last_part = get_lp_dollar(str, *index -1, data, first_part);
	free(*str);
	if (!first_part && !last_part)
	{
		(*str) = NULL;
		return ;
	}
	else if (!first_part)
		(*str) = ft_strdup(last_part);
	else if (!last_part)
		(*str) = ft_strdup(first_part);
	else
		(*str) = ft_strjoin(first_part, last_part);
	if (first_part)
		free(first_part);
	if (last_part)
		free(last_part);
	if (!(*str))
		ex_malloc(NULL, NULL, data);
}

char	*get_first_part_clear(char **str, int until, t_data *data)
{
	int		i;
	char	*first_part;

	i = 0;
	if (until == 0)
		return (NULL);
	first_part = malloc((until + 1) * sizeof(char));
	if (!first_part)
		ex_malloc(NULL, (*str), data);
	while (i < until)
	{
		first_part[i] = (*str)[i];
		i++;
	}
	first_part[i] = '\0';
	return (first_part);
}

//modif -> 30/04 :
//al_str -> char a free si malloc fail
//st_to -> start to 
//lp ->last part
static char	*get_lp_dollar(char **str, int st_to, t_data *data, char *al_str)
{
	int		start;
	char	*last_part;

	if ((*str)[st_to] == '$')
		st_to++;
	while ((*str)[st_to] && (ft_isalnum((*str)[st_to])
		|| (*str)[st_to] == '_'))
		st_to++;
	if ((*str)[st_to] == '\0')
		return (NULL);
	if ((*str)[st_to - 1] == '$' && (*str)[st_to] == '"')
		st_to++;
	start = st_to;
	last_part = help_lp_dollar(str, start, data, al_str);
	return (last_part);
}

char	*help_lp_dollar(char **str, int start, t_data *data, char *al_str)
{
	char	*last_part;
	int		size;
	int		i;

	size = 0;
	i = start;
	while ((*str)[i++])
		size++;
	last_part = malloc((size + 1) * sizeof(char));
	if (!last_part)
	{
		free(al_str);
		ex_malloc(NULL, (*str), data);
	}
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
