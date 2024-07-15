/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:58:20 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 09:57:56 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

static char	**get_env(t_data *data);
static void	fill_ep(char ***my_ep, t_data *data);
static char	**get_arg_v(t_arg **arg, t_data *data);
static void	fill_av(char ***my_av, t_arg **arg, t_data *data);

void	exec_command(t_arg **arg, t_data *data)
{
	t_exec	info;

	info.my_envp = NULL;
	info.my_argv = NULL;
	info.path_envp = NULL;
	info.path_name = NULL;
	if (arg == NULL || (*arg)->str == NULL)
	{
		free_data(&data);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
	info.path_envp = get_path_envp(data);
	info.path_name = find_pathnam(arg, &info.path_envp, data);
	if (info.path_name == NULL)
		ex_no_cmd(arg, data, &(info));
	info.my_argv = get_arg_v(arg, data);
	info.my_envp = get_env(data);
	execve(info.path_name, info.my_argv, info.my_envp);
	if (info.my_argv)
		get_free(info.my_argv);
	if (info.my_envp)
		get_free(info.my_envp);
	exit_execve(arg, data, &(info));
}

//fonction qui permet de passer la structure env en tableau **
//protected
static char	**get_env(t_data *data)
{
	t_env	*tmp;
	int		i;
	char	**my_envp;

	i = 0;
	if (!data->env)
		return (NULL);
	tmp = *(data->env);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	my_envp = malloc((i + 1) * sizeof(char *));
	if (!my_envp)
		ex_malloc(NULL, NULL, data);
	fill_ep(&my_envp, data);
	return (my_envp);
}

static void	fill_ep(char ***my_ep, t_data *data)
{
	t_env	*tmp;
	int		i;

	tmp = *(data->env);
	i = 0;
	while (tmp)
	{
		if (!tmp->value || tmp->value[0] == '\0')
		{
			(*my_ep)[i] = ft_strdup(tmp->var);
			if (!(*my_ep)[i])
				ex_malloc((*my_ep), NULL, data);
		}
		else
		{
			(*my_ep)[i] = ft_strjoin(tmp->var, tmp->value);
			if (!(*my_ep)[i])
				ex_malloc((*my_ep), NULL, data);
		}
		tmp = tmp->next;
		i++;
	}
	(*my_ep)[i] = NULL;
}

static char	**get_arg_v(t_arg **arg, t_data *data)
{
	t_arg	*tmp;
	int		i;
	char	**my_argv;

	i = 0;
	tmp = *arg;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	my_argv = malloc((i + 1) * sizeof(char *));
	if (!my_argv)
		ex_malloc(NULL, NULL, data);
	fill_av(&my_argv, arg, data);
	return (my_argv);
}

static void	fill_av(char ***my_av, t_arg **arg, t_data *data)
{
	t_arg	*tmp;
	int		i;

	tmp = *arg;
	i = 0;
	while (tmp)
	{
		(*my_av)[i] = ft_strdup(tmp->str);
		if (!(*my_av)[i])
		{
			get_free((*my_av));
			ex_malloc(NULL, NULL, data);
		}
		i++;
		tmp = tmp->next;
	}
	(*my_av)[i] = NULL;
}
