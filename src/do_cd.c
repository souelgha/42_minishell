/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:54:12 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 14:44:54 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

static int	help_do_cd(t_data *data, char **getcwd_s);

int	do_cd(t_arg **arg, t_data *data)
{
	char	*getcwd_s;

	getcwd_s = getcwd(NULL, 0);
	if ((!((*arg)->next)) || (ft_strncmp((*arg)->next->str, "~", 2) == 0))
		return (help_do_cd(data, &getcwd_s));
	else if ((*arg)->next->next)
		ft_fprintf(2, "cd : too many arguments\n");
	else if (ft_strncmp((*arg)->next->str, "-", 2) == 0)
		help_do_cd_oldpwd(arg, data);
	else if (chdir((*arg)->next->str) == 0)
	{
		maj_pwd(data);
		if (getcwd_s)
			free(getcwd_s);
		return (0);
	}
	else if (chdir((*arg)->next->str) < 0 || getcwd_s == NULL)
		return (error_management_cd(arg, data, &getcwd_s));
	maj_pwd(data);
	if (getcwd_s)
		free(getcwd_s);
	return (1);
}

static int	help_do_cd(t_data *data, char **getcwd_s)
{
	char	*home_dir;

	if (*getcwd_s)
		free(*getcwd_s);
	home_dir = get_home_dir(data);
	if (!home_dir)
		return (1);
	if (ft_strncmp(home_dir, "VALUEVIDE", ft_strlen(home_dir)) == 0)
		return (0);
	chdir(home_dir);
	free(home_dir);
	maj_pwd(data);
	return (0);
}

int	help_do_cd_oldpwd(t_arg **arg, t_data *data)
{
	char	*old_dir;

	old_dir = get_old_pwd(data);
	if (!old_dir)
		ex_malloc(NULL, NULL, data);
	printf("%s\n", old_dir);
	if (chdir(old_dir) < 0)
		perror((*arg)->next->str);
	free(old_dir);
	return (0);
}

int	error_management_cd(t_arg **arg, t_data *data, char **getcwd_s)
{
	if (ft_strncmp((*arg)->next->str, "--", 2) == 0)
	{
		if ((*getcwd_s))
			free(*getcwd_s);
		ft_fprintf(2, "cd : %s: invalid option\n", (*arg)->next->str);
		return (2);
	}
	else if (!(*getcwd_s))
	{
		ft_fprintf(2, "cd : error retrieving current directory: ");
		maj_pwd(data);
		return (1);
	}
	else
		return (helping_cd(arg, data, getcwd_s));
	return (0);
}

char	*get_home_dir(t_data *data)
{
	char	*home_dir;
	t_env	*tmp;

	tmp = *(data->env);
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "HOME=", 5) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_fprintf(2, "minishell: HOME not set\n");
		return (NULL);
	}
	if (!tmp->value)
		return ("VALUEVIDE");
	home_dir = ft_strdup(tmp->value);
	if (!home_dir)
		ex_malloc(NULL, NULL, data);
	return (home_dir);
}
