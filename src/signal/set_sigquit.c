/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sigquit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:42:34 by dardo-na          #+#    #+#             */
/*   Updated: 2023/04/07 23:46:14 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "helper.h"

static void    handle_interrupt(int signal)
{
    (void)signal;
    rl_on_new_line();
}

static void    set_quit_hook(void)
{
    signal_hook(get_signal(), handle_interrupt, SIGQUIT);
}

void    set_quit_signal(void)
{
    set_quit_hook();
}