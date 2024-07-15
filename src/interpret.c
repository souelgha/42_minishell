/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:22:37 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 14:19:21 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//chercher le caractère "$" dans notre str de base
//et si on voit un double quotes -> on doit chercher le caractère dedans
//on recoit un pointeur sur notre str pour pouvoir la modifier au besoin
//on ne fait RIEN si c'est entre single quotes 
//(rien ne doit jamais etre modifier entre single quotes)
// ligne 46 : -1 pour revenir au char $ du prochain puisquon 
//a effacer le premier
void	interpret(char **str, t_data *data)
{
	int		i;
	char	*limite;
	char	*recept;

	limite = NULL;
	i = 0;
	while ((*str)[i])
	{
		if (limite)
		{
			if (ft_strncmp(limite, (*str) + i, ft_strlen(limite) - 1) == 0)
			{
				i += ft_strlen(limite);
				free(limite);
				limite = NULL;
			}
		}
		recept = choose(&i, str, data);
		if (recept)
			limite = recept_exist(&recept);
		if (check_end(str, i, limite) == 1)
			return ;
		i++;
	}
}

char	*recept_exist(char **recept)
{
	char	*limite;

	limite = NULL;
	limite = ft_strdup(*recept);
	free(*recept);
	*recept = NULL;
	return (limite);
}

int	check_end(char **str, int i, char *limite)
{
	if (!(*str) || (*str)[i] == '\0')
	{
		if (limite)
			free(limite);
		return (1);
	}
	return (0);
}
