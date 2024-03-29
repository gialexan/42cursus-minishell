/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interative.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:31:33 by dardo-na          #+#    #+#             */
/*   Updated: 2023/04/07 21:43:15 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "helper.h"

void	turnoff_interrupt_signal(void)
{
	signal_hook(get_signal(), SIG_IGN, SIGINT);
}

void	turnoff_quit_signal(void)
{
	signal_hook(get_signal(), SIG_IGN, SIGQUIT);
}

void	turnoff_signals(void)
{
	turnoff_interrupt_signal();
	turnoff_quit_signal();
}
