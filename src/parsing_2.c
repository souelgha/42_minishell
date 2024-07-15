/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:32:14 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 11:43:29 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_parsing(t_arg	**parsed, t_redirect **info, char **str, t_data *data)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == ' ' || (*str)[i] == '\t' || (*str)[i] == '\'')
			help_while_bcl(&str, &i, &parsed, &status);
		else if ((*str)[i] == '"')
			help_parsing_dq(&str, &i, &parsed, &status);
		else if ((*str)[i] == '<' || (*str)[i] == '>')
			status = redirection_parsing(info, str, &i, data);
		else
			help_parsing_s(&str, &i, &parsed, &status);
		if (status < 0)
			return (status);
		if ((*str)[i] == '\0')
			break ;
		if (status == 1)
			break ;
		i++;
	}
	return (0);
}
