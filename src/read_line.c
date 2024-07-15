/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:51:17 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 11:52:11 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

extern int	g_sig;
static int	check_letter(char c, char d);

char	*read_until(char *prompt_line, t_data *data)
{
	char	*tmp;
	char	*readed;
	int		start;

	start = 0;
	tmp = readline(prompt_line);
	if (g_sig == 2)
	{
		g_sig = -1;
		data->status = 130;
	}
	if (tmp == NULL)
		help_tmp_null(prompt_line, data);
	if (tmp[0] == '\0')
	{
		free(tmp);
		return (NULL);
	}
	readed = check_readed_line(tmp, &start, data);
	free(tmp);
	if (readed == NULL)
		return (NULL);
	return (readed);
}

//les quotes et doubles quotes ne sont interprété que quand ils sont fermé
//st = start
char	*check_readed_line(char *str, int *st, t_data *data)
{
	char	*tmp;

	if (syn_manag(str, data) == 1)
		return (NULL);
	tmp = help_check_readed_line(str, st, data);
	return (tmp);
}

char	*help_check_readed_line(char *str, int *st, t_data *data)
{
	char	*tmp;

	tmp = ft_strdup(str);
	data->ex_g_fd = dup(STDIN_FILENO);
	while (tmp[*st])
	{
		if (check_letter(tmp[*st], tmp[*st + 1]) != 0)
			return (syntax_error(tmp, st, data));
		if (tmp[*st] == '"' && help_double_quotes(&tmp, str, st, data) == 1)
			return (NULL);
		if (tmp[*st] == '\'' && help_quotes(&tmp, str, st, data) == 1)
			return (NULL);
		if (tmp[*st] == '<' && is_this_a_heredoc(tmp, st) == 0
			&& help_here_doc(&tmp, st, data) == 1)
		{
			free(tmp);
			return (NULL);
		}
		if (tmp[*st] == '\\')
			*st += 1;
		(*st)++;
	}
	close(data->ex_g_fd);
	data->ex_g_fd = -1;
	return (tmp);
}

//c est le caractere qu'on regarde et d est le caractere d'apres
static int	check_letter(char c, char d)
{
	if ((c == '\\' && d == '\0') || (c == ';')
		|| (c == ')' || (c == '!')
			|| (c == '|' && d == '\0')))
		return (1);
	return (0);
}

int	is_this_a_heredoc(char *tmp, int *st)
{
	if ((*st) > 0)
	{
		if (tmp[*st - 1] != '<' && tmp[*st] == '<'
			&& tmp[*st + 1] == '<' && tmp[*st + 2] != '<')
			return (0);
	}
	else
	{
		if (tmp[*st] == '<' && tmp[*st + 1] == '<' && tmp[*st + 2] != '<')
			return (0);
		else
			return (1);
	}
	return (1);
}
