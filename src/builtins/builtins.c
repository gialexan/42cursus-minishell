/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:50:18 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/07 15:45:04 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(const char *str)
{
    int length;

	if (!str)
		return (-1);
    length = ft_strlen(str);
	if (!strncmp(str, FT_ECHO, length))
		return (0);
	else if (!strncmp(str, FT_CD, length))
		return (1);
	else if (!strncmp(str, FT_PWD, length))
		return (2);
    else if (!strncmp(str, FT_ENV, length))
		return (3);
	else if (!strncmp(str, FT_EXIT, length))
		return (4);
    else if (!strncmp(str, FT_UNSET, length))
		return (5);
    else if (!strncmp(str, FT_EXPORT, length))
	    return (6);
	return (-1);
}

void	fork_bultin(const t_builtin builtin, t_list *token, t_data *data)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(data->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(data->fd[STDOUT_FILENO], STDOUT_FILENO);      
		data->retcode = builtin(token);
		if (data->fdclose >= 0)
			close(data->fdclose);
		close(data->fd[STDIN_FILENO]);
		close(data->fd[STDOUT_FILENO]);
		msh_clear();
		exit(data->retcode);
	}
	if (data->fd[STDIN_FILENO] != STDIN_FILENO)
		close(data->fd[STDIN_FILENO]);
	if (data->fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(data->fd[STDOUT_FILENO]);
}