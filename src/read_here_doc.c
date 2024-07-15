/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:06:06 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 13:44:39 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

static int	ex_syntax_fail(t_data *data);
static int	check_end_hdoc(char *lim, char *rea, char **str, t_data *data);
static int	read_join(char **tmp, char *lim, char **cpy_readed, t_data *data);
static void	got_eoc(char **tmp, char **end_of_cmd, char *limite, t_data *data);

int	help_here_doc(char **tmp, int *start, t_data *data)
{
	char	*limite;
	char	*cpy_readed;
	char	*end_of_cmd;

	limite = get_limite(tmp, start, data, 0);
	if (!limite)
		return (ex_syntax_fail(data));
	end_of_cmd = get_rest_after_pipe(limite, tmp, data);
	while ((*tmp)[*start])
		(*start)++;
	cpy_readed = NULL;
	while (check_end_hdoc(limite, cpy_readed, tmp, data) != 1)
	{
		if (read_join(tmp, limite, &cpy_readed, data) == 1)
			return (1);
	}
	free(cpy_readed);
	*start = ft_strlen(*tmp) - 1;
	if (end_of_cmd)
		got_eoc(tmp, &end_of_cmd, limite, data);
	free(limite);
	signal_research();
	return (0);
}

static int	check_end_hdoc(char *limite, char *readed, char **str, t_data *data)
{
	char	*tmp;

	tmp = ft_strjoin((*str), "\n");
	if (!tmp)
	{
		free(limite);
		free(readed);
		ex_malloc(NULL, (*str), data);
	}
	free(*str);
	*str = NULL;
	*str = ft_strdup(tmp);
	if (!(*str))
	{
		free(limite);
		free(readed);
		ex_malloc(NULL, (tmp), data);
	}
	free(tmp);
	if (readed == NULL)
		return (0);
	if (ft_strncmp(limite, readed, ft_strlen(limite) + 1) == 0)
		return (1);
	return (0);
}

//got_eoc = End Of Command
static void	got_eoc(char **tmp, char **end_of_cmd, char *limite, t_data *data)
{
	char	*str;

	str = ft_strdup((*tmp));
	if (!str)
		ex_malloc_bis(NULL, *end_of_cmd, (*tmp), data);
	free((*tmp));
	*tmp = NULL;
	*tmp = join_str_here_doc(str, end_of_cmd, limite, data);
}

static int	ex_syntax_fail(t_data *data)
{
	ft_fprintf(2, "minishell: syntax error near"
		" unexpected token « newline »\n");
	data->status = 2;
	return (1);
}

//protected
static int	read_join(char **tmp, char *limite, char **cpy_readed, t_data *data)
{
	char	*readed;
	char	*str;

	ignore_sig();
	signal_read_line();
	if ((*cpy_readed) != NULL)
		free((*cpy_readed));
	str = ft_strdup((*tmp));
	if (!str)
		ex_malloc_bis(NULL, limite, (*tmp), data);
	free((*tmp));
	readed = readline(">");
	if (readed)
	{
		(*cpy_readed) = ft_strdup(readed);
		if (!(*cpy_readed))
			ex_malloc_bis(NULL, limite, readed, data);
	}
	*tmp = join_str_here_doc(str, &readed, limite, data);
	if (!(*tmp))
	{
		free(limite);
		return (1);
	}
	return (0);
}
