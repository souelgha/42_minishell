/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 22:17:27 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 16:59:10 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	boucle(char **str, int *i);
static int	choice(char **str, int *i);
static int	interpret_dollar(char **str, t_data *data, int *index);
static void	interpret_doubleq_dollar(char **str, t_data *data, int *index);

char	*choose(int *i, char **str, t_data *data)
{
	char	*limite;
	int		status;

	status = 0;
	limite = NULL;
	status = choice(str, i);
	if (status == 1)
		boucle(str, i);
	else if (status == 2)
		interpret_doubleq_dollar(str, data, i);
	else if (status == 3 || status == 4)
		(*i)++;
	else if (status == 5)
	{
		interpret_dollar(str, data, i);
		(*i) -= 1;
	}
	else if (status == 6)
		(*i)++;
	else if (status == 7)
		limite = get_limite(str, i, NULL, 0);
	return (limite);
}

static void	boucle(char **str, int *i)
{
	(*i)++;
	while ((*str)[*i] && (*str)[*i] != '\'')
		(*i)++;
}

static int	choice(char **str, int *i)
{
	int	status;

	status = 0;
	if ((*str)[*i] == '\'')
		status = 1;
	else if ((*str)[*i] == '"')
		status = 2;
	else if ((*str)[*i] == '\\' && (*str)[(*i) + 1] != '\0')
		status = 3;
	else if ((*str)[*i] == '$' && (*str)[(*i) + 1] != '\0'
			&& ((*str)[(*i) + 1] == ':' || (*str)[(*i) + 1] == ' '
			|| (*str)[(*i) + 1] == '='))
		status = 4;
	else if ((*str)[*i] == '$' && (*str)[(*i) + 1] != '\0'
			&& (*str)[(*i) + 1] != '$')
		status = 5;
	else if ((*str)[*i] == '$' && (*str)[(*i) + 1] != '$')
		status = 6;
	else if ((*str)[*i] == '<' && is_this_a_heredoc((*str), i) == 0)
		status = 7;
	return (status);
}

//on va regarder si on a une variable d'environnement,
//une variable dernier exit status reçue
//une variable qui demande le pid du process en cours ?
/**ajout du cas ou on a $digit *****/
static int	interpret_dollar(char **str, t_data *data, int *index)
{
	char	*value;

	(*index)++;
	if ((*str)[*index] == '\0')
		return (1);
	if ((*str)[*index] == '?')
	{
		value = replace(data->status);
		fill_in(str, value, index, data);
		free(value);
		return (0);
	}
	if (ft_isdigit((*str)[*index]))
		clean_isnum_dollar(str, data);
	else
		help_interpret_dollar(str, data, index);
	return (0);
}

//fonction qui permet de se deplacer entre les double quotes 
//et au besoin d'appeler 
//la fonction qui interpret le $
static void	interpret_doubleq_dollar(char **str, t_data *data, int *index)
{
	(*index)++;
	while ((*str)[*index] && (*str)[*index] != '"')
	{
		if ((*str)[*index] == '$' && ((*str)[*index + 1] != '\0')
			&& ((*str)[*index + 1] == '"'))
		{
			index += 1;
			break ;
		}
		if ((*str)[*index] == '$' && ((*str)[*index + 1] != '\0'
			&& (*str)[*index + 1] != '$' && (*str)[*index + 1] != ' '))
		{
			interpret_dollar(str, data, index);
			*index -= 1;
		}
		else if ((*str)[*index] == '$' && (*str)[*index + 1] != '$')
			(*index)++;
		if ((*str)[*index] == '\0')
			break ;
		(*index)++;
	}
}
