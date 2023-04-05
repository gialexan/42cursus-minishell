/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:14:13 by dardo-na          #+#    #+#             */
/*   Updated: 2023/04/05 14:55:05 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

static void	handle_interrupt(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	set_interrupt_hook(void)
{
	signal_hook(get_signal(), handle_interrupt, SIGINT);
}

void	set_interactive_hooks(void)
{
	set_interrupt_hook();
	turnoff_quit_signal();
}
