/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_checkname_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:06:54 by sonouelg          #+#    #+#             */
/*   Updated: 2024/05/18 12:49:26 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

// static int	while_check_name(t_arg *arg, char *built);
// static int	check_name_var(t_arg *arg, char *built);
// static int	check_first_char_var(t_arg *arg, char *built);

// commentaires a ajouter sur l'interet de cette fonction 
int	while_check_name(t_arg *arg, char *built)
{
	t_arg	*tmp_ar;
	int		i;
	int		status;

	i = 0;
	status = 0;
	tmp_ar = arg;
	while (tmp_ar->str[i] && tmp_ar->str[i] != '=')
	{
		if ((!ft_isalnum(tmp_ar->str[i])) && (tmp_ar->str[i] != '_')
			&& (tmp_ar->str[i] != '"'))
		{
			ft_fprintf(2, "%s: `%s\' : not a"
				" valid identifier\n", built, tmp_ar->str);
			status = 1;
			break ;
		}
		i++;
	}
	return (status);
}

/*** check des noms de variables 1 par une ******/
int	check_name_var(t_arg *arg, char *built)
{
	t_arg	*tmp_ar;
	int		status;

	status = 0;
	tmp_ar = arg;
	if (ft_isdigit(tmp_ar->str[0]))
	{
		ft_fprintf(2, "%s: `%s\' : not a"
			" valid identifier\n", built, (tmp_ar->str));
		status = 1;
		return (status);
	}
	if ((tmp_ar->str[0] == '\0') || (((tmp_ar->str[0]) == '=')))
	{
		ft_fprintf(2, "%s: `%s\' : not a valid "
			"identifier\n", built, tmp_ar->str);
		status = 1;
		return (status);
	}
	status = while_check_name(arg, built);
	return (status);
}

/** check du 1er char apres export si c est '-' on arrete le prog ******/
int	check_first_char_var(t_arg *arg, char *built)
{
	t_arg	*tmp_ar;
	int		status;

	status = 1;
	tmp_ar = arg;
	if (tmp_ar->str[0] == '-')
	{
		ft_fprintf(2, "%s: %c%c:"
			" invalid option\n", built, tmp_ar->str[0], tmp_ar->str[1]);
		status = 2;
		return (status);
	}
	if (tmp_ar->str[0] == '/' && ft_strncmp(built, "unset", 5) == 0)
		status = 0;
	return (status);
}
