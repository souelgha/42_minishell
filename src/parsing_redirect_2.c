/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirect_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:18:27 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 14:20:11 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok 17

int	redirection_here_doc(t_redirect *curr, char **str, int *index, int start)
{
	int	fd_origin;
	int	size;

	size = get_size_redir(str, &start);
	fd_origin = dup(STDOUT_FILENO);
	if (fd_origin == -1)
		return (-3);
	ft_strcpy_redir(curr->red, (*str), start, size + 1);
	curr->fd_here_doc = create_temp_file(curr->red);
	if (curr->fd_here_doc == -1)
		return (-3);
	if (complete_here_doc(curr->red, (*str), index, fd_origin) == -1)
		return (-1);
	clear_str(str, index, curr->red);
	if ((*str)[*index] == '\0')
		return (1);
	return (0);
}

void	clear_str(char **str, int *index, char *limite)
{
	char	*last_part;
	char	*tmp;

	tmp = ft_strjoin(limite, "\n");
	while (check_limite(tmp, (*str), *index, ft_strlen(limite) + 1) != 0)
		(*index)++;
	free(tmp);
	last_part = get_last_part_clear_str(str, *index + 1);
	free(*str);
	*str = ft_strdup(last_part);
	free(last_part);
	(*index) = 0;
}

char	*get_last_part_clear_str(char **str, int index)
{
	int		size;
	int		i;
	char	*get_last_part;

	size = 0;
	while ((*str)[index] && ((*str)[index] != '<' && (*str)[index] != ' '
		&& (*str)[index] != '\n'))
		index++;
	i = index;
	while ((*str)[i++])
		size++;
	get_last_part = malloc((size + 1) * sizeof(char));
	if (!get_last_part)
		return (NULL);
	size = 0;
	while ((*str)[index])
	{
		get_last_part[size] = (*str)[index];
		index++;
		size++;
	}
	get_last_part[size] = '\0';
	return (get_last_part);
}

int	create_temp_file(char *limite)
{
	int		fd;
	char	*joined;

	joined = ft_strjoin("/tmp/", limite);
	fd = open(joined, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (-1);
	if (dup2(fd, 1) == -1)
		ex_dup2(NULL);
	close(fd);
	free(joined);
	return (fd);
}

int	complete_here_doc(char *limite, char *str, int *index, int fd_origin)
{
	int		i;

	i = *index;
	while (str[i] != '\n')
		i++;
	while (str[i])
	{
		if (str[i] == '\n' && check_limite(limite, str, i + 1,
				ft_strlen(limite)) == 0)
		{
			write(1, &str[i], 1);
			dup2(fd_origin, 1);
			if (close(fd_origin) == -1)
				return (-1);
			return (0);
		}
		write(1, &str[i], 1);
		i++;
	}
	if (dup2(fd_origin, 1) == -1)
		return (-1);
	if (close(fd_origin) == -1)
		return (-1);
	return (0);
}
