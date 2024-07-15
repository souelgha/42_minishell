/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_outils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:57:47 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 11:17:40 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok
extern int	g_sig;

int	help_double_quotes(char **tmp, char *str, int *start, t_data *data)
{
	*start += 1;
	ignore_sig();
	while (check_double_quotes(tmp, start, data) != 1)
	{
		signal_read_line();
		str = ft_strdup((*tmp));
		if (!str)
			ex_malloc(NULL, str, data);
		free((*tmp));
		*tmp = NULL;
		*tmp = join_arg(&str, readline(">"), '"', data);
		if (!(*tmp))
		{
			free(str);
			ignore_sig();
			return (1);
		}
	}
	ignore_sig();
	return (0);
}

int	help_quotes(char **tmp, char *str, int *start, t_data *data)
{
	*start += 1;
	ignore_sig();
	while (check_quotes(tmp, start, data) != 1)
	{
		signal_read_line();
		str = ft_strdup((*tmp));
		if (!str)
			ex_malloc(NULL, str, data);
		free((*tmp));
		*tmp = NULL;
		*tmp = join_arg(&str, readline(">"), '\'', data);
		if (!(*tmp))
		{
			free(str);
			ignore_sig();
			return (1);
		}
	}
	ignore_sig();
	return (0);
}

//fonction qui va joindre la char deja lu avec la char qui viens d'etre lu
char	*join_arg(char **old, char *new, char c, t_data *data)
{
	char	*arg;

	if (g_sig == 2)
		return (g_fd_is_not_minus_one(*old, new, data));
	if (new == NULL)
	{
		data->status = 2;
		if (data->ex_g_fd != -1)
			close(data->ex_g_fd);
		ft_fprintf(2, "minishell : unexpected EOF while "
			"looking for matching « %c »\nminishell : "
			"syntax error: unexpected end of file\n", c);
		return (NULL);
	}
	arg = ft_strjoin((*old), new);
	free((*old));
	free(new);
	if (!arg)
		ex_malloc(NULL, NULL, data);
	return (arg);
}

void	*g_fd_is_not_minus_one(char *old, char *new, t_data *data)
{
	if (dup2(data->ex_g_fd, 0) == -1)
	{
		free(old);
		free(new);
		ex_dup2(data);
	}
	if (close(data->ex_g_fd) == -1)
	{
		free(old);
		free(new);
		ex_close_fail(data);
	}
	data->ex_g_fd = -1;
	return (NULL);
}

void	help_strnstr(const char *big, size_t *j)
{
	if (big[*j] == '"')
	{
		(*j)++;
		while (big[*j] && big[*j] != '"')
			(*j)++;
	}
	if (big[*j] == '\'')
	{
		(*j)++;
		while (big[*j] && big[*j] != '\'')
			(*j)++;
	}
}
