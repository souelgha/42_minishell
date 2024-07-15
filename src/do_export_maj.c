/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export_maj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:23:15 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 16:49:10 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme PAS OK 14/05
//mauvais file_name dans headers

static int	maj_env_w(t_data *data, char **tab, int clic);
static int	maj_var(t_env *curv, char ***tab_tmp, t_data *data);
static int	help_maj_env_w_1(t_data *data, char **tab, t_env *tenv, char **tmp);
static int	help_maj_env_w_2(t_data *data, char **tab, t_env *tenv, char **tmp);

/****  maj de env si la variable existe ****/
int	maj_env(t_arg *var, t_data *data)
{
	t_arg	*targ;
	int		status;
	char	**tab;

	targ = var;
	tab = splitted_var(targ->str, data);
	status = maj_env_w(data, tab, 0);
	if (status != 0)
		return (status);
	get_free(tab);
	return (0);
}

static int	maj_env_w(t_data *data, char **tab, int clic)
{
	t_env	*tenv;
	char	*tmp;

	tenv = *(data->env);
	if (tab[0][ft_strlen(tab[0])] != '=')
	{
		tmp = ft_strjoin(tab[0], "=");
		clic = 1;
	}
	while (tenv)
	{
		if (clic == 1 && (ft_strncmp(tenv->var, tmp, ft_strlen(tmp) + 1) == 0))
		{
			free(tmp);
			get_free(tab);
			return (2);
		}
		else if ((ft_strncmp(tenv->var, tab[0], ft_strlen(tab[0]) + 1) == 0))
			return (help_maj_env_w_1(data, tab, tenv, &tmp));
		else if ((ft_strncmp(tenv->var, tab[0], ft_strlen(tenv->var)) == 0))
			return (help_maj_env_w_2(data, tab, tenv, &tmp));
		tenv = tenv->next;
	}
	free(tmp);
	return (0);
}

static int	help_maj_env_w_2(t_data *data, char **tab, t_env *tenv, char **tmp)
{
	if (*tmp)
		free(*tmp);
	if ((ft_strlen(tenv->var)) == ft_strlen(tab[0]) - 1)
		return (maj_var(tenv, &tab, data));
	return (0);
}

static int	help_maj_env_w_1(t_data *data, char **tab, t_env *tenv, char **tmp)
{
	if (*tmp)
		free(*tmp);
	if ((ft_strlen(tenv->var)) == ft_strlen(tab[0]))
		return (maj_var(tenv, &tab, data));
	else
	{
		get_free(tab);
		return (2);
	}
}

/***** mise a jour de la valeur de la variable 
 * si la var = "var" sans le '=' on met a jour la variable *****/
static int	maj_var(t_env *curv, char ***tab_tmp, t_data *data)
{
	int	size;

	size = ft_strlen(curv->var);
	free(curv->value);
	if (ft_strncmp(curv->var, (*tab_tmp)[0], size) == 0)
	{
		free(curv->var);
		curv->var = ft_strdup((*tab_tmp)[0]);
		if (!curv->var)
			ex_malloc((*tab_tmp), NULL, data);
	}
	if ((*tab_tmp)[1])
	{
		curv->value = ft_strdup((*tab_tmp)[1]);
		if (!curv->value)
			ex_malloc((*tab_tmp), NULL, data);
	}
	else
		curv->value = NULL;
	get_free((*tab_tmp));
	return (1);
}
