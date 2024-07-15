/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command_path_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:02:30 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 11:27:38 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 14/05

static void	last_check(char ***t_path, char *cmd_str, t_data *data);
static char	*findp(char ***t_path, t_data *data, char *cmd_str);

//1 : regarde si on a un chemin absolue
	//1.1 :oui: regarde si c'est un directory
			//1.1.1 :oui: verifie si on veut l'executer
				//1.1.1.1 :oui: exit -> erreur -> (directory)
				//1.1.1.2 :non: retourne 1.2.
			//1.1.2 :non: return le path tel quel.
	//1.2 :non: retourne 2.
//2 : parcours tout les path possible
	//2.1 :find:oui: retourne le path tel quel.
	//2.2 :find:non: regarde si on demande a executer ->(./ ou / devant)
		//2.2.1 :oui: no such file or directory
		//2.2.2 :non: retourne 2.3
	//2.3 : return NULL.

char	*find_pathnam(t_arg **a_c, char ***t_path, t_data *data)
{
	char	*command_str;
	char	*full_join;
	int		status;

	if (access(((*a_c)->str), F_OK) == 0)
	{
		full_join = ft_strdup((*a_c)->str);
		if (!full_join)
			ex_malloc(NULL, NULL, data);
		status = check_directory(full_join);
		if (status == 1)
			ex_direc(&full_join, t_path, data);
		if (status == 0)
			return (full_join);
		if (status == 2)
			free(full_join);
	}
	if ((*t_path) == NULL)
		ex_no_such(a_c, data);
	command_str = ft_strjoin("/", (*a_c)->str);
	if (!command_str)
		ex_malloc(NULL, NULL, data);
	return (findp(t_path, data, command_str));
}

int	check_directory(char *path_name)
{
	struct stat	info;
	mode_t		mode;

	stat(path_name, &info);
	mode = info.st_mode;
	if (!S_ISDIR(mode) && access((path_name), X_OK) == 0)
		return (0);
	else if (S_ISDIR(mode) && (ft_strncmp("./", path_name, 2) == 0
			|| ft_strncmp("/", path_name, 1) == 0
			|| path_name[ft_strlen(path_name) - 1] == '/'))
		return (1);
	else if (S_ISDIR(mode) || (ft_strchr(path_name, '.') != NULL
			&& ft_strncmp(".", path_name, 1) != 0))
		return (2);
	else if (access((path_name), X_OK) != 0
		&& ft_strncmp("./", path_name, 2) == 0)
		return (0);
	else if (access((path_name), X_OK) != 0)
		return (2);
	return (0);
}

//find path_name
static char	*findp(char ***t_path, t_data *data, char *cmd_str)
{
	int		i;
	char	*full_join;

	i = 0;
	while ((*t_path)[i])
	{
		full_join = ft_strjoin((*t_path)[i], cmd_str);
		if (!full_join)
			ex_malloc(NULL, cmd_str, data);
		if (access(full_join, F_OK | X_OK) == 0)
		{
			if (check_directory(full_join) != 2)
			{
				free(cmd_str);
				get_free((*t_path));
				*t_path = NULL;
				return (full_join);
			}
		}
		free(full_join);
		i++;
	}
	last_check(t_path, cmd_str, data);
	return (NULL);
}

static void	last_check(char ***t_path, char *cmd_str, t_data *data)
{
	get_free((*t_path));
	*t_path = NULL;
	if (ft_strncmp("//", cmd_str, 2) == 0
		|| ft_strncmp("/./", cmd_str, 3) == 0)
	{
		ft_fprintf(2, "Minishell : %s: "
			"No such file or directory\n", cmd_str + 1);
		free(cmd_str);
		rl_clear_history();
		if (data)
			free_data(&data);
		exit(127);
	}
	free(cmd_str);
}
