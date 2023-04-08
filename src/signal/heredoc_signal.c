/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:33:53 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 03:29:21 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "helper.h"

static void    handle_interrupt(int signal)
{
    (void)signal;
    ft_putstr_fd("\n", STDOUT_FILENO);
    //quit_shell();
    printf("oi\n");
    msh_clear();
    exit(1);
}

static void    set_interrupt_hook(void)
{
    signal_hook(get_signal(), handle_interrupt, SIGINT);
}

void    set_hdoc_hooks(void)
{
    set_interrupt_hook();
    turnoff_quit_signal();
}