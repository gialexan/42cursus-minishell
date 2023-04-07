/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:48:35 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/07 16:00:49 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static t_bool	is_abspath(char *path);

void	refresh_data(t_data *data)
{
	data->fd[STDIN_FILENO] = STDIN_FILENO;
	data->fd[STDOUT_FILENO] = STDOUT_FILENO;
	data->error = FALSE;
	data->fdclose = -1;
}

t_bool	exec_execve(t_list *token, t_data *data, t_bool builtin)
{
	if (!token || builtin)
		return (FALSE);
	else if (is_abspath(token->content))
		return (exec_abspath(token, data));
	return (exec_nopath(token, data));
}

static t_bool	is_abspath(char *path)
{
	if (ft_strchr("./", path[0]) == 0)
		return (FALSE);
	return (TRUE);
}
