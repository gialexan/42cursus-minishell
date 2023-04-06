/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:26:24 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/05 23:17:44 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "helper.h"

typedef struct sigaction	t_sigaction;
typedef void				(*t_signal)(int);

void    fork_hook(void);
void	set_quit_signal(void);
void	turnoff_quit_signal(void);
void	set_interactive_hooks(void);
void	turnoff_interrupt_signal(void);
void    signal_hook(t_sigaction *action, t_signal handler, int signal);

#endif