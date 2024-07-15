/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_here_doc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:59:23 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 17:17:15 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

char	*get_limite(char **tmp, int *start, t_data *data, int size)
{
	int		i;
	char	*limite;

	size = ft_get_size_limite(tmp, start);
	if (size == -1)
		return (NULL);
	limite = malloc((size + 1) * sizeof(char));
	if (!limite)
		ex_malloc(NULL, (*tmp), data);
	i = *start;
	size = 0;
	while ((*tmp)[i] != '\0' && ((*tmp)[i] != ' ' && (*tmp)[i] != '\t'
		&& (*tmp)[i] != '\n'))
	{
		if ((*tmp)[i] == '"' || (*tmp)[i] == '\'')
			i++;
		else
		{
			limite[size] = (*tmp)[i];
			size++;
			i++;
		}
	}
	limite[size] = '\0';
	return (limite);
}

int	ft_get_size_limite(char **tmp, int *start)
{
	int		i;
	int		size;

	*start += 2;
	while ((*tmp)[*start] && ((*tmp)[*start] == ' ' || (*tmp)[*start] == '\t'))
		(*start)++;
	if ((*tmp)[*start] == '\0')
		return (-1);
	i = *start;
	size = 0;
	while ((*tmp)[i] != '\0' && (*tmp)[i] != ' ' && (*tmp)[i] != '\t'
		&& (*tmp)[i] != '\n')
	{
		if ((*tmp)[i] == '"' || (*tmp)[i] == '\'')
			i++;
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

char	*get_rest_after_pipe(char *limite, char **tmp, t_data *data)
{
	int		size_first;
	int		size_rest;
	char	*tempo;
	char	*rest;

	size_first = 0;
	size_rest = 0;
	tempo = ft_strdup((*tmp));
	if (!tempo)
		ex_malloc_bis(NULL, limite, (*tmp), data);
	if (get_both_size(limite, tmp, &size_first, &size_rest) == -1)
	{
		free(tempo);
		return (NULL);
	}
	free((*tmp));
	*tmp = malloc((size_first + 1) * sizeof(char));
	if (!(*tmp))
		ex_malloc_bis(tempo, limite, NULL, data);
	rest = help_g_r_a_p(size_rest, limite, tempo, tmp);
	if (!rest)
		ex_malloc_bis(limite, tempo, (*tmp), data);
	free(tempo);
	return (rest);
}

char	*help_g_r_a_p(int size_rest, char *limite, char *tempo, char **tmp)
{
	int		i;
	char	*rest;

	i = 0;
	rest = malloc((size_rest + 1) * sizeof(char));
	if (!(rest))
		return (NULL);
	while (tempo[i] && check_limite(limite, tempo, i, ft_strlen(limite)) != 0)
	{
		(*tmp)[i] = tempo[i];
		i++;
	}
	while (tempo[i] && tempo[i] != '\n' && tempo[i] != ' ' && tempo[i] != '\t')
	{
		(*tmp)[i] = tempo[i];
		i++;
	}
	(*tmp)[i] = '\0';
	size_rest = 0;
	while (tempo[i++])
		rest[size_rest++] = tempo[i];
	rest[size_rest] = '\0';
	return (rest);
}

int	get_both_size(char *limite, char **tmp, int *size_first, int *size_rest)
{
	int		i;

	i = 0 ;
	while ((*tmp)[i] && check_limite(limite, (*tmp), i, ft_strlen(limite)) != 0)
		i++;
	while ((*tmp)[i] && (*tmp)[i] != '\n'
		&& (*tmp)[i] != ' ' && (*tmp)[i] != '\t')
		i++;
	if ((*tmp)[i] == '\0')
		return (-1);
	(*size_first) = i;
	while ((*tmp)[i])
	{
		i++;
		(*size_rest)++;
	}
	return (0);
}
