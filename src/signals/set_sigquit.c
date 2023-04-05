/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sigquit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:42:34 by dardo-na          #+#    #+#             */
/*   Updated: 2023/04/05 14:54:51 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

static void	handle_interrupt(int signal)
{
	(void)signal;
	printf("\nSigquit!!\n");
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	ft_lstclear(get_envp(), free);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

static void	set_quit_hook(void)
{
	signal_hook(get_signal(), handle_interrupt, SIGQUIT);
}

void	set_quit_signal(void)
{
	set_quit_hook();
}
