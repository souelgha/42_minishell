/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:46:19 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/23 11:46:36 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_research_fork(void)
{
	struct sigaction	action;

	action.sa_handler = control_c_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	action.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &action, NULL);
}
