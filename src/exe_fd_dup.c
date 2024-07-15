/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_fd_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:43:26 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/22 10:27:01 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norme ok

static void	hwhd(t_redirect *tmp, t_info_fd *fd, t_data *data);

void	ex_cmd(t_data *data)
{
	int	status;

	status = data->status;
	free_data(&data);
	rl_clear_history();
	exit(status);
}

//check_wait_here_doc
void	whd(t_redirect *tmp, t_info_fd *fd, t_data *data)
{
	pid_t		pid;
	int			status;

	while (tmp)
	{
		if (tmp->token == 3)
		{
			(void)fd;
			wait(&status);
			pid = fork();
			if (pid == -1)
				ex_pid("pid", NULL);
			if (pid == 0)
				hwhd(tmp, fd, data);
			else
				wait(&status);
		}
		tmp = tmp->next;
	}
}

static void	hwhd(t_redirect *tmp, t_info_fd *fd, t_data *data)
{
	char		**argv_here_doc;
	char		*joined;

	if (close(tmp->fd_here_doc) == -1)
		ex_close_fail(data);
	if (dup2(fd->oldfd_in, 0) == -1)
		ex_dup2(data);
	if (close(fd->oldfd_in) == -1)
		ex_close_fail(data);
	joined = ft_strjoin("/tmp/", tmp->red);
	if (!joined)
		ex_malloc(NULL, NULL, data);
	argv_here_doc = erase_temp_file(joined, data);
	free(joined);
	execve("/usr/bin/rm", argv_here_doc, NULL);
}

char	**erase_temp_file(char *to_erase, t_data *data)
{
	char	**argv_here_doc;

	argv_here_doc = NULL;
	argv_here_doc = malloc(3 * sizeof(char *));
	if (!argv_here_doc)
		ex_malloc(NULL, to_erase, data);
	argv_here_doc[0] = ft_strdup("rm");
	if (!argv_here_doc[0])
		ex_malloc(NULL, to_erase, data);
	argv_here_doc[1] = ft_strdup(to_erase);
	if (!argv_here_doc[1])
	{
		get_free(argv_here_doc);
		ex_malloc(NULL, to_erase, data);
	}
	argv_here_doc[2] = NULL;
	return (argv_here_doc);
}
