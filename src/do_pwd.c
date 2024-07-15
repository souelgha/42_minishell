/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:54:12 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 17:08:46 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

static void	help_pwd(void);

//reçoit la liste chaine qui stock l'env
//va rechercher dans env pour trouver la bonne variable
/*********regarder si PWD existe dans env *****/
int	find_pwd(t_data *data)
{
	t_env	*tmp;
	int		find;

	find = 0;
	tmp = *(data->env);
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PWD=", 4) == 0)
		{
			find = 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (find);
}

/*********affiche pwd *****/
int	do_pwd(t_arg **arg, t_data *data)
{
	t_env	*tmp;

	tmp = *(data->env);
	if ((*arg)->next && (ft_strncmp((*arg)->next->str, "-", 1) == 0))
	{
		ft_fprintf(2, "pwd : Options for pwd not managed!!\n");
		return (2);
	}
	else if (!find_pwd(data))
		help_pwd();
	else
	{
		while (ft_strncmp(tmp->var, "PWD=", 4) != 0)
			tmp = tmp->next;
		if (tmp->value)
			printf("%s\n", tmp->value);
		else
			help_pwd();
	}
	return (0);
}

static void	help_pwd(void)
{
	char	*getcwd_s;

	getcwd_s = NULL;
	getcwd_s = getcwd(NULL, 0);
	if (getcwd_s)
	{
		printf("%s\n", getcwd_s);
		free(getcwd_s);
	}
}
