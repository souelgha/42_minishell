/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:31:31 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 11:38:47 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//NORME OK

int	token_management(char *str, int *index, t_data *data)
{
	if (erreur_management(str, index, data) == 1)
		return (-1);
	while (str[*index] && (str[*index] == '<' || str[*index] == '>'))
		(*index)++;
	while (str[*index] && (str[*index] == ' ' || str[*index] == '\t'))
		(*index)++;
	if (str[*index] == '\0' || (str[ft_strlen(str) - 1] == '>'
			&& str[ft_strlen(str)] == '\0') || (str[ft_strlen(str) - 1] == '<'
			&& str[ft_strlen(str)] == '\0'))
	{
		if (str[*index - 1] == '<' && ((*index) - 1) > 1)
		{
			data->status = 2;
			ft_fprintf(2, "minishell: syntax error"
				" near unexpected token << < >>\n");
			return (-1);
		}
		data->status = 2;
		ft_fprintf(2, "BLAminishell: syntax error"
			" near unexpected token <<newline>>\n");
		return (-1);
	}
	return (0);
}

int	erreur_management(char *str, int *index, t_data *data)
{
	int	i;

	i = *index;
	if (str[i] == '>' && str[i + 1] == '<' && str[i + 2] == '>')
	{
		data->status = 2;
		ft_fprintf(2, "minishell: syntax error near unexpected token « <> »\n");
		return (1);
	}
	else if (str[i] == '>')
		return (erreur_management_bis(str, index, data));
	else if (str[i] == '<' && str[i + 1] == '>' && str[i + 2] == '<')
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token « <> »\n");
		return (1);
	}
	else if (str[i] == '<')
		return (erreur_management_bis_2(str, index, data));
	return (0);
}

int	erreur_management_bis(char *str, int *index, t_data *data)
{
	int	count;
	int	i;

	count = 0;
	i = *index;
	while (str[i] && (str[i] == '>'))
	{
		i++;
		if (str[i] == '>')
			count++;
	}
	if (count == 3)
	{
		data->status = 2;
		ft_fprintf(2, "minishell: syntax error near unexpected token « > »\n");
		return (1);
	}
	else if (count > 3)
	{
		data->status = 2;
		ft_fprintf(2, "minishell: syntax error near unexpected token « >> »\n");
		return (1);
	}
	return (0);
}

int	erreur_management_bis_2(char *str, int *index, t_data *data)
{
	int	count;
	int	i;

	count = 0;
	i = *index;
	while (str[i] == '<')
	{
		i++;
		count++;
	}
	if (count == 4)
	{
		data->status = 2;
		ft_fprintf(2, "minishell: syntax error near unexpected token « < »\n");
		return (1);
	}
	else if (count > 4)
	{
		data->status = 2;
		ft_fprintf(2, "minishell: syntax error near unexpected token « << »\n");
		return (1);
	}
	return (0);
}

int	get_token(char *str, int finded_at)
{
	if (str[finded_at] == '>' && str[finded_at + 1] == '>')
		return (1);
	else if (str[finded_at] == '<' && str[finded_at + 1] == '>')
		return (2);
	else if (str[finded_at] == '>' && str[finded_at + 1] == '<')
	{
		ft_fprintf(2, "minishell : syntax error near "
			"unexpected token « %c »\n", str[finded_at + 1]);
		return (-1);
	}
	else if (str[finded_at] == '>' && str[finded_at + 1] != '>')
		return (2);
	else if (str[finded_at] == '<' && str[finded_at + 1] == '<')
		return (3);
	else if (str[finded_at] == '<' && str[finded_at + 1] != '<')
		return (4);
	else
		return (0);
}
