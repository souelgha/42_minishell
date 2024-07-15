/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:02:46 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 15:20:40 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		join_two_last_node(t_arg **parsed);

void	help_while_bcl(char ***str, int *i, t_arg ***parsed, int *status)
{
	if ((**str)[*i] == ' ' || (**str)[*i] == '\t')
	{
		while ((**str)[*i] && ((**str)[(*i) + 1] == ' '
			|| (**str)[(*i) + 1] == '\t'))
			(*i)++;
		*status = 5;
	}
	else if ((**str)[*i] == '\'')
		help_parsing_q(str, i, parsed, status);
}

void	help_parsing_s(char ***str, int *i, t_arg ***parsed, int *status)
{
	int	last_status;

	last_status = *status;
	if ((**parsed) == NULL || (**str)[(*i) - 1] == ' '
		|| (**str)[(*i) - 1] == '\t'
		|| (**str)[(*i) - 1] == '<' || (**str)[(*i) - 1] == '>')
	{
		*status = space_parsing(*parsed, (**str), i);
		if (last_status == 5 && *status == 2)
			*status = 4;
	}
	else
	{
		*status = space_parsing(*parsed, (**str), i);
		if ((last_status == 2 && *status == 1)
			|| (last_status == 3 && *status == 3)
			|| (last_status == 3 && *status == 1))
			join_two_last_node(*parsed);
	}
	(*i) -= 1;
}

//checked
void	help_parsing_dq(char ***str, int *i, t_arg ***parsed, int *status)
{
	int	last_status;

	last_status = *status;
	if ((**parsed) == NULL || (**str)[(*i) - 1] == ' '
		|| (**str)[(*i) - 1] == '\t')
	{
		*status = double_quotes_parsing(*parsed, (**str), i);
		if (last_status == 5 && *status == 2)
			*status = 4;
	}
	else
	{
		*status = double_quotes_parsing(*parsed, (**str), i);
		if ((last_status == 2 && *status == 1)
			|| (last_status == 3 && *status == 3))
			join_two_last_node(*parsed);
	}
}

//checked
void	help_parsing_q(char ***str, int *i, t_arg ***parsed, int *status)
{
	int	last_status;

	last_status = *status;
	if ((**parsed) == NULL || (**str)[(*i) - 1] == ' '
		|| (**str)[(*i) - 1] == '\t')
	{
		*status = quotes_parsing(*parsed, (**str), i);
		if (last_status == 5 && *status == 2)
			*status = 4;
	}
	else
	{
		*status = quotes_parsing(*parsed, (**str), i);
		if ((last_status == 2 && *status == 1)
			|| (last_status == 3 && *status == 3))
			join_two_last_node(*parsed);
	}
}

static void	join_two_last_node(t_arg **parsed)
{
	t_arg	*tmp;
	t_arg	*tmp_bl;
	char	*tmp_str;

	tmp = (*parsed);
	while (tmp->next)
	{
		tmp_bl = tmp;
		tmp = tmp->next;
	}
	tmp_str = ft_strjoin(tmp_bl->str, tmp->str);
	free(tmp_bl->str);
	free(tmp->str);
	free(tmp);
	tmp_bl->str = ft_strdup(tmp_str);
	free(tmp_str);
	tmp_bl->next = NULL;
}
