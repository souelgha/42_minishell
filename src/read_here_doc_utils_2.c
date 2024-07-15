/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_here_doc_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:50:11 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 13:54:45 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

extern int	g_sig;

int	check_limite(char *limite, char *str, int j, int size)
{
	int	i;

	i = 0;
	while (limite[i] && limite[i] == str[j] && i < size - 1)
	{
		i++;
		j++;
	}
	return ((unsigned char)limite[i] - (unsigned char)str[j]);
}

char	*join_str_here_doc(char *old, char **new, char *limite, t_data *data)
{
	char	*arg;

	if (g_sig != -1)
		return (gf_d_not_minus_join(&old, new, &limite, data));
	else if (*new == NULL)
	{
		free(old);
		if (data->ex_g_fd != -1)
			close(data->ex_g_fd);
		ft_fprintf(2, "avertissement : « here-document »"
			" délimité par la fin du fichier (au lieu de « %s »)\n", limite);
		return (NULL);
	}
	arg = ft_strjoin(old, *new);
	free(old);
	free(*new);
	if (!arg)
		ex_malloc(NULL, limite, data);
	return (arg);
}

void	*gf_d_not_minus_join(char **old, char **new, char **lim, t_data *data)
{
	if (dup2(data->ex_g_fd, 0) == -1)
	{
		free(*old);
		free(*new);
		free(*lim);
		ex_dup2(data);
	}
	if (close(data->ex_g_fd) == -1)
	{
		free(*old);
		free(*new);
		free(*lim);
		ex_close_fail(data);
	}
	free(*old);
	data->ex_g_fd = -1;
	return (NULL);
}
