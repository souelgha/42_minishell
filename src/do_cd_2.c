/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:43:52 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 14:49:29 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

char	*get_old_pwd(t_data *data)
{
	t_env	*tmp;

	tmp = *(data->env);
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "OLDPWD=", 7) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	helping_cd(t_arg **arg, t_data *data, char **getcwd_s)
{
	char	*pterror;

	if (*getcwd_s)
		free((*getcwd_s));
	pterror = ft_strjoin("cd : ", (*arg)->next->str);
	if (!pterror)
		ex_malloc(NULL, NULL, data);
	perror(pterror);
	free(pterror);
	return (1);
}
