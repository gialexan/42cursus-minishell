/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fork_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:07:15 by dardo-na          #+#    #+#             */
/*   Updated: 2023/04/09 15:13:45 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "helper.h"

static void	handle_interrupt(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static void	handle_quit(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (core dumpt)\n", STDOUT_FILENO);
}

static void	set_interrupt_hook(void)
{
	signal_hook(get_signal(), handle_interrupt, SIGINT);
}

static void	set_quit_hook(void)
{
	signal_hook(get_signal(), handle_quit, SIGQUIT);
}

void	fork_hook(void)
{
	set_interrupt_hook();
	set_quit_hook();
}
