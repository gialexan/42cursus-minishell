/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:11:36 by dardo-na          #+#    #+#             */
/*   Updated: 2023/04/05 14:54:48 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void	signal_hook(t_sigaction *action, t_signal handler, int signal)
{
	action->sa_handler = handler;
	action->sa_flags = SA_RESTART;
	sigemptyset(&action->sa_mask);
	sigaction(signal, action, NULL);
}
