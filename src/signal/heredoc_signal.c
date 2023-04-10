/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:33:53 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/09 15:11:38 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "helper.h"

static void	handle_interrupt(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	clear_heredoc();
	exit(EXIT_SUCCESS);
}

static void	set_interrupt_hook(void)
{
	signal_hook(get_signal(), handle_interrupt, SIGINT);
}

void	set_hdoc_hooks(void)
{
	set_interrupt_hook();
	turnoff_quit_signal();
}
