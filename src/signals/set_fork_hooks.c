/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fork_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:07:15 by dardo-na          #+#    #+#             */
/*   Updated: 2023/04/05 14:55:01 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

static void	handle_interrupt(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

static void	set_interrupt_hook(void)
{
	signal_hook(get_signal(), handle_interrupt, SIGINT);
}

void	fork_hook(void)
{
	set_interrupt_hook();
}
