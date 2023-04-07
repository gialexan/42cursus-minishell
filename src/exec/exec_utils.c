/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:48:35 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/07 18:07:24 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

#define ENOENT 2
#define EACCES 13
#define EISDIR 21

static t_bool	is_abspath(char *path);

t_bool	is_executable(t_list *token)
{
	char *path;
	struct stat sb;

	path = token->content;
	if (access(path, F_OK))
	{
		msh_error(path, NULL, ENOENT);
		set_exit_code(127);
		return (FALSE);
	}
	else if (access(path, X_OK))
	{
		msh_error(path, NULL, EACCES);
		set_exit_code(126);
		return (FALSE);
	}
	stat(path, &sb);
	if (sb.st_mode & S_IFDIR)
	{
		msh_error(path, NULL, EISDIR);
		set_exit_code(126);
		return (FALSE);
	}
}

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
