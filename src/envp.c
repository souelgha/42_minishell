/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:53:25 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 09:55:49 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme OK 14/05

static int	check(t_data *data, char *current_dir);
static void	do_old_pwd(t_data *data, char *old_pwd);
static int	envp_empty(t_data *data);

void	env_cpy(char **envp, t_data *data, int i, int j)
{
	char	*var_1;
	char	*value_1;

	if ((!envp || !envp[0]) && envp_empty(data) == 0)
		return ;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		var_1 = malloc((j + 2) * sizeof(char));
		if (!var_1)
			ex_malloc(NULL, NULL, data);
		ft_strlcpy(var_1, envp[i], j + 2);
		if (envp[i][j] == '\0')
			value_1 = NULL;
		else
			value_1 = malloc((ft_strlen(envp[i]) - j) * sizeof(char));
		ft_strscpy(value_1, envp[i], j + 1);
		get_nodded(var_1, value_1, data);
		free_char(var_1, value_1);
		i++;
	}
}

/* mis à jour du PWD et du OLDPWD*/
//protected
void	maj_pwd(t_data *data)
{
	char	*current_dir;
	char	*old_pwd;
	t_env	*tmp;

	tmp = *(data->env);
	current_dir = getcwd(NULL, 0);
	if (check(data, current_dir) == 1)
		return ;
	while (ft_strncmp(tmp->var, "PWD=", 4) != 0)
		tmp = tmp->next;
	if (!tmp->value)
		old_pwd = ft_strdup("");
	else
		old_pwd = ft_strdup(tmp->value);
	if (!old_pwd)
		ex_malloc(NULL, NULL, data);
	free(tmp->value);
	tmp->value = ft_strdup(current_dir);
	if (!tmp->value)
	{
		free(old_pwd);
		ex_malloc(NULL, current_dir, data);
	}
	free(current_dir);
	do_old_pwd(data, old_pwd);
}

static void	do_old_pwd(t_data *data, char *old_pwd)
{
	t_env	*tmp;

	tmp = *(data->env);
	while (tmp && ft_strncmp(tmp->var, "OLDPWD=", 7) != 0)
		tmp = tmp->next;
	free(tmp->value);
	tmp->value = ft_strdup(old_pwd);
	if (!tmp->value)
		ex_malloc(NULL, old_pwd, data);
	free(old_pwd);
}

static int	check(t_data *data, char *current_dir)
{
	if (!find_pwd(data))
	{
		if (current_dir)
			free(current_dir);
		return (1);
	}
	if (!current_dir)
	{
		ft_fprintf(2, "getcwd: cannot access parent directories:"
			"  file or directory\n");
		return (1);
	}
	return (0);
}

static int	envp_empty(t_data *data)
{
	char	*currentdir;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup("OLDPWD");
	tmp2 = ft_strdup("");
	get_nodded(tmp, tmp2, data);
	free(tmp);
	free(tmp2);
	currentdir = getcwd(NULL, 0);
	tmp = ft_strdup("PWD=");
	get_nodded(tmp, currentdir, data);
	free(tmp);
	tmp = ft_strdup("SHLVL=");
	tmp2 = ft_strdup("1");
	get_nodded("SHLVL=", "1", data);
	free(tmp);
	free(tmp2);
	tmp = ft_strdup("_=");
	tmp2 = ft_strdup("/usr/bin/env");
	get_nodded("_=", "/usr/bin/env", data);
	free(currentdir);
	free(tmp);
	free(tmp2);
	return (0);
}
