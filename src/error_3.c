/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:58:14 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 09:52:19 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

//free(command, str1, str2, env)
void	ex_malloc_bis(char *str_1, char *str_2, char *str_3, t_data *data)
{
	ft_fprintf(2, "malloc : corrupted top size\n"
		"Abandon (core dumped)\n");
	if (str_1)
		free(str_1);
	if (str_2)
		free(str_2);
	if (str_3)
		free(str_3);
	if (data)
		free_data(&data);
	if (data->ex_g_fd != -1)
		close(data->ex_g_fd);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	ex_close_fail(t_data *data)
{
	perror("close");
	rl_clear_history();
	free_data(&data);
	exit(EXIT_FAILURE);
}

char	*syntax_error(char *tmp, int *st, t_data *data)
{
	ft_fprintf(2, "Minishell: syntax error near"
		" unexpected token « %c »\n", tmp[*st]);
	free(tmp);
	data->status = 2;
	return (NULL);
}

void	ex_direc(char **fil, char ***t_path, t_data *data)
{
	int	status;

	status = 126;
	if ((*fil))
	{
		ft_fprintf(2, "Minishell : %s: Is a directory\n", *fil);
		free(*fil);
		fil = NULL;
	}
	if (data)
		free_data(&data);
	if ((*t_path))
		get_free((*t_path));
	*t_path = NULL;
	data = NULL;
	rl_clear_history();
	exit(status);
}

void	ex_no_such(t_arg **a_c, t_data *data)
{
	ft_fprintf(2, "Minishell: %s: No such file or directory\n", (*a_c)->str);
	if (data)
		free_data(&data);
	rl_clear_history();
	exit(127);
}
