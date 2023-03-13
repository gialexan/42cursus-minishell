/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:27:43 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 19:01:30 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

void	show_error(char *msg, char *error)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if(!error)
		return ;
	ft_putendl_fd(error, STDERR_FILENO);
}
