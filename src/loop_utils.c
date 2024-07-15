/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:16:42 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/21 15:05:43 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

static char	*help_find_home_dir(char *g_cwd, t_data *data);

/***trouver la string apres home pour le prompt ****/
//ligne 35 : modif marianne cause leak 29/04
char	*find_endpwd(t_data *data)
{
	char	*home;
	char	*cur_pwd;
	char	*end_pwd;
	size_t	i;

	i = 0;
	home = find_home_dir(data);
	cur_pwd = find_currentdir(data);
	if (!home)
		return (cur_pwd);
	while (home[i] == cur_pwd[i] && cur_pwd[i])
		i++;
	if (i == ft_strlen(cur_pwd))
	{
		free(home);
		free(cur_pwd);
		return (NULL);
	}
	free(home);
	end_pwd = strdup(&cur_pwd[i]);
	if (!end_pwd)
		ex_malloc(NULL, cur_pwd, data);
	free(cur_pwd);
	return (end_pwd);
}

char	*currentdir_null(t_data *data)
{
	t_env	*tmp;
	char	*current;

	current = NULL;
	tmp = *(data->env);
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PWD=", 4) == 0)
		{
			current = ft_strdup(tmp->value);
			if (!current)
				ex_malloc(NULL, NULL, data);
			break ;
		}
		tmp = tmp->next;
	}
	return (current);
}

/****trouver le current directory*****/
char	*find_currentdir(t_data *data)
{
	char	*currentdir;
	char	*current;

	current = NULL;
	currentdir = getcwd(NULL, 0);
	if (!currentdir)
	{
		current = currentdir_null(data);
		return (current);
	}
	if (ft_strncmp(currentdir, "/", 1) == 0)
	{
		current = ft_strdup(currentdir);
		if (!current)
			ex_malloc(NULL, currentdir, data);
	}
	free(currentdir);
	return (current);
}

/*****recup du chemin de home *****/
// ligne 99 :modif marianne cause leak 29/04
char	*find_home_dir(t_data *data)
{
	char	*current;
	char	*g_cwd;

	current = NULL;
	g_cwd = getcwd(NULL, 0);
	if (!g_cwd)
	{
		current = currentdir_null(data);
		return (current);
	}
	if (ft_strncmp(g_cwd, "/", 1) == 0)
		current = help_find_home_dir(g_cwd, data);
	free(g_cwd);
	return (current);
}

static char	*help_find_home_dir(char *g_cwd, t_data *data)
{
	char	*current;
	t_env	*tmp;

	current = NULL;
	tmp = *(data->env);
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "HOME=", 5) == 0)
		{
			if (!(tmp->value))
				return (NULL);
			current = ft_strdup(tmp->value);
			if (!current)
				ex_malloc(NULL, g_cwd, data);
		}
		tmp = tmp->next;
	}
	return (current);
}
