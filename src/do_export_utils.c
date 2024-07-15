/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:23:15 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/17 18:57:24 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme pas ok

static void	help_cpy_tab(char **tab_arg, char *str, int i);

int	get_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=' && str[i + 1] != '\0')
		return (2);
	else
		return (1);
}

void	cpy_tab(char **tab_arg, char *str, int size)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		tab_arg[0][i] = str[i];
		i++;
	}
	if (ft_strchr(str, '='))
	{
		tab_arg[0][i] = '=';
		tab_arg[0][i + 1] = '\0';
	}
	else
		tab_arg[0][i] = '\0';
	if (size == 2)
		help_cpy_tab(tab_arg, str, i);
}

static void	help_cpy_tab(char **tab_arg, char *str, int i)
{
	int	size;

	size = 0;
	i += 1;
	while (str[i])
	{
		tab_arg[1][size] = str[i];
		size++;
		i++;
	}
	tab_arg[1][size] = '\0';
}

int	init_tab_arg(char **tab_arg, char *str, int size)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		tab_arg[0] = malloc((i + 1) * sizeof(char));
	else
		tab_arg[0] = malloc((i + 2) * sizeof(char));
	if (!tab_arg[0])
	{
		free(tab_arg);
		return (-1);
	}
	if (size == 2)
	{
		if (help_init_tab(tab_arg, str, size, i) == -1)
			return (-1);
	}
	return (0);
}

int	help_init_tab(char **tab_arg, char *str, int size, int i)
{
	size = 0;
	i += 1;
	while (str[i])
	{
		size++;
		i++;
	}
	tab_arg[1] = malloc((size + 1) * sizeof(char));
	if (!tab_arg[1])
	{
		get_free(tab_arg);
		return (-1);
	}
	return (0);
}
