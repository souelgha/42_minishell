/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:05:00 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 11:46:40 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "minishell.h"
// SIGINT = ctrl-c
// SIGQUIT = ctrl-\//
// VERIFIER SI PROTECTION SUR SIGACTION A FAIRE
// VERIFIER SI FERMETURE FDS A FAIRE

int	g_sig = -1;

void	control_c_handler(int num)
{
	if (num == SIGINT)
	{
		g_sig = num;
		write(0, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_research(void)
{
	struct sigaction	action;

	action.sa_handler = control_c_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGTSTP, &action, NULL);
}

void	control_c_handler_readline(int num)
{
	g_sig = num;
	write(0, "\n", 1);
	close(0);
}

void	signal_read_line(void)
{
	struct sigaction	action;

	action.sa_handler = control_c_handler_readline;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
}

void	ignore_sig(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		ft_fprintf(2, "nope\n");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_fprintf(2, "nope nope\n");
}
