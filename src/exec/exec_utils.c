/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:48:35 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/06 14:51:31 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	refresh_data(t_data *data)
{
	data->fd[STDIN_FILENO] = STDIN_FILENO;
	data->fd[STDOUT_FILENO] = STDOUT_FILENO;
	data->error = FALSE;
}

void	redirect_io(int saved[], t_data *data)
{
	saved[STDIN_FILENO] = STDIN_FILENO;
	saved[STDOUT_FILENO] = STDOUT_FILENO;
	if (data->fd[STDIN_FILENO] != STDIN_FILENO)
	{
		saved[STDIN_FILENO] = dup(STDIN_FILENO);
		dup2(data->fd[STDIN_FILENO], STDIN_FILENO);
		close(data->fd[STDIN_FILENO]);
	}
	if (data->fd[STDOUT_FILENO] != STDOUT_FILENO)
	{
		saved[STDOUT_FILENO] = dup(STDOUT_FILENO);
		dup2(data->fd[STDOUT_FILENO], STDOUT_FILENO);
		close(data->fd[STDOUT_FILENO]);
	}
}

void	restore_io(int saved[])
{
	if (saved[STDIN_FILENO] != STDIN_FILENO)
	{
		dup2(saved[STDIN_FILENO], STDIN_FILENO);
		close (saved[STDIN_FILENO]);
	}
	if (saved[STDOUT_FILENO] != STDOUT_FILENO)
	{
		dup2(saved[STDOUT_FILENO], STDOUT_FILENO);
		close (saved[STDOUT_FILENO]);
	}
}
