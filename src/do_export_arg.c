/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:06:54 by sonouelg          #+#    #+#             */
/*   Updated: 2024/05/21 10:05:02 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

static void	lets_export(t_arg *arg, t_data *data);

int	do_export_arg(t_arg **arg, t_data *data)
{
	t_arg	*tmp_ar;
	int		check_name;
	int		status;
	int		ret_maj;

	status = 0;
	ret_maj = 0;
	tmp_ar = (*arg)->next;
	check_name = check_first_char_var(tmp_ar, "export");
	if (check_name == 2)
		return (check_name);
	while (tmp_ar)
	{
		check_name = check_name_var(tmp_ar, "export");
		if (check_name != 0)
			status = check_name;
		else if (check_name == 0)
		{
			ret_maj = maj_env(tmp_ar, data);
			if (!ret_maj)
				lets_export(tmp_ar, data);
		}
		tmp_ar = tmp_ar->next;
	}
	return (status);
}

//protected
/***ajout d une nouvelle variable d environnement si elle n existe pas*****/
static void	lets_export(t_arg *arg, t_data *data)
{
	t_arg	*tmp_ar;
	t_env	*tmp_env;
	char	**tab_tmp;

	tmp_ar = arg;
	tab_tmp = splitted_var(tmp_ar->str, data);
	tmp_env = *(data->env);
	while (tmp_env->next)
		tmp_env = tmp_env->next;
	tmp_env->next = add_node();
	if (!tmp_env->next)
		ex_malloc(tab_tmp, NULL, data);
	tmp_env->next->var = ft_strdup(tab_tmp[0]);
	if (!tmp_env->next->var)
		ex_malloc(tab_tmp, NULL, data);
	if (tab_tmp[1])
	{
		tmp_env->next->value = ft_strdup(tab_tmp[1]);
		if (!tmp_env->next->value)
			ex_malloc(tab_tmp, tmp_env->next->var, data);
	}
	get_free(tab_tmp);
	tab_tmp = NULL;
}

char	**splitted_var(char	*str, t_data *data)
{
	int		size;
	char	**tab_arg;

	size = get_size(str);
	tab_arg = malloc((size + 1) * sizeof(char *));
	if (!tab_arg)
		ex_malloc(NULL, str, data);
	tab_arg[size] = NULL;
	if (init_tab_arg(tab_arg, str, size) == -1)
		ex_malloc(NULL, str, data);
	cpy_tab(tab_arg, str, size);
	return (tab_arg);
}
