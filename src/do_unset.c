/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:54:12 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 11:45:43 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme OK 14/05

static void	help_do_unset(t_env *tmp_env, t_env *tmp_env_current, t_data *data);
static int	check_options(t_arg **arg);
static void	unset_help(t_env **tenv, t_arg *targ, t_env **tenv_current);
static int	check_first_char(t_arg *arg);

/***** pas de protection necessaire *******/
/*****ajout des check options *****/
int	do_unset(t_arg **arg, t_data *data)
{
	t_env	*tenv;
	t_env	*tenv_current;
	t_arg	*targ;
	int		check;
	int		status;

	status = 0;
	check = check_options(arg);
	if (check == 0 || check == 2)
		return (check);
	targ = (*arg)->next;
	while (targ)
	{
		if (check == 3)
		{
			tenv = *(data->env);
			tenv_current = tenv;
			unset_help(&tenv, targ, &tenv_current);
			if (tenv)
				help_do_unset(tenv, tenv_current, data);
		}
		targ = targ->next;
	}
	return (status);
}

static void	unset_help(t_env **tenv, t_arg *targ, t_env **tenv_current)
{
	while (*tenv)
	{
		if (ft_strncmp((*tenv)->var, targ->str,
				(ft_strlen((*tenv)->var) - 1)) == 0)
			break ;
		(*tenv_current) = (*tenv);
		*tenv = (*tenv)->next;
	}
}

static int	check_options(t_arg **arg)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	if (!(*arg)->next)
		return (0);
	if ((*arg)->next->str[0] == '\0')
		return (0);
	status = check_first_char((*arg)->next);
	if (status == 2)
		return (status);
	if ((*arg)->next->str[ft_strlen((*arg)->next->str) - 1] == '=')
		return (1);
	return (3);
}

static void	help_do_unset(t_env *tmp_env, t_env *tmp_env_current, t_data *data)
{
	t_env	**env;

	env = (data->env);
	if (ft_strncmp(tmp_env->var, (*env)->var, (ft_strlen((*env)->var))) == 0)
	{
		free(tmp_env->var);
		if (tmp_env->value)
			free(tmp_env->value);
		(*env) = tmp_env->next;
		free(tmp_env);
		return ;
	}
	if (!tmp_env->next)
		tmp_env_current->next = NULL;
	else
		tmp_env_current->next = tmp_env->next;
	free(tmp_env->var);
	if (tmp_env->value)
		free(tmp_env->value);
	free(tmp_env);
}

static int	check_first_char(t_arg *arg)
{
	t_arg	*tmp_ar;
	int		status;

	status = 3;
	tmp_ar = arg;
	if (tmp_ar->str[0] == '-')
	{
		ft_fprintf(2, "unset: %c%c:"
			" invalid option\n", tmp_ar->str[0], tmp_ar->str[1]);
		status = 2;
		return (status);
	}
	if (tmp_ar->str[0] == '/')
		status = 1;
	return (status);
}
