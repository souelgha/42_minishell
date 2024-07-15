/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:35:59 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 14:18:46 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prompt_line(t_data *data);
static char	*get_prompt_line_help_one(t_data *data, char *end_pwd);
static char	*get_prompt_line_help_two(t_data *data, char *end_pwd);

extern int	g_sig;

int	loop_minishell(t_data *data)
{
	char		*tmp;
	char		*prompt_line;

	prompt_line = NULL;
	tmp = NULL;
	while (1)
	{
		signal_research();
		prompt_line = get_prompt_line(data);
		tmp = read_until(prompt_line, data);
		if (!tmp)
			free(prompt_line);
		else if (tmp && tmp[0] != '\0')
		{
			if (loop_bis(prompt_line, data, &tmp) == 1)
				break ;
		}
		else if (tmp[0] == '\0')
		{
			free(tmp);
			free(prompt_line);
		}
	}
	return (data->status);
}

int	loop_bis(char *prompt_line, t_data *data, char **tmp)
{
	add_history((*tmp));
	interpret(tmp, data);
	if (!(*tmp))
	{
		free(prompt_line);
		return (0);
	}
	parsing((*tmp), data);
	if (data->command)
	{
		free(prompt_line);
		free((*tmp));
		direct_command(data);
		if (data->command)
		{
			free_command_list(&(data->command));
			data->command = NULL;
		}
	}
	else
	{
		free(prompt_line);
		free((*tmp));
	}
	return (0);
}

/******modification du prompt ********/
static char	*get_prompt_line(t_data *data)
{
	char	*end_pwd;
	char	*prompt_line;
	char	*tmp;

	end_pwd = find_endpwd(data);
	if (!end_pwd)
	{
		prompt_line = ft_strjoin("own_minishell:~", "$ ");
		if (!prompt_line)
			ex_malloc(NULL, NULL, data);
	}
	else
	{
		tmp = find_home_dir(data);
		if (!tmp)
			prompt_line = get_prompt_line_help_one(data, end_pwd);
		else
		{
			free(tmp);
			prompt_line = get_prompt_line_help_two(data, end_pwd);
		}
	}
	return (prompt_line);
}

static char	*get_prompt_line_help_one(t_data *data, char *end_pwd)
{
	char	*current_dir;
	char	*tmp;
	char	*prompt_line;

	free(end_pwd);
	current_dir = find_currentdir(data);
	tmp = ft_strjoin("own_minishell:", current_dir);
	free(current_dir);
	if (!tmp)
		ex_malloc(NULL, NULL, data);
	prompt_line = ft_strjoin(tmp, "$ ");
	if (!prompt_line)
		ex_malloc(NULL, tmp, data);
	free(tmp);
	return (prompt_line);
}

static char	*get_prompt_line_help_two(t_data *data, char *end_pwd)
{
	char	*tmp;
	char	*prompt_line;

	prompt_line = ft_strjoin("own_minishell:", "~");
	if (!prompt_line)
		ex_malloc(NULL, end_pwd, data);
	tmp = ft_strjoin(prompt_line, end_pwd);
	free(prompt_line);
	free(end_pwd);
	if (!tmp)
		ex_malloc(NULL, NULL, data);
	prompt_line = ft_strjoin(tmp, "$ ");
	if (!prompt_line)
		ex_malloc(NULL, tmp, data);
	free(tmp);
	return (prompt_line);
}
