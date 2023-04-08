/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:50:18 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 17:55:32 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(char *str)
{
	if (!str)
		return (-1);
	else if (ft_strcmp(str, FT_ECHO) == 0)
		return (0);
	else if (ft_strcmp(str, FT_CD) == 0)
		return (1);
	else if (ft_strcmp(str, FT_PWD) == 0)
		return (2);
    else if (ft_strcmp(str, FT_ENV) == 0)
		return (3);
	else if (ft_strcmp(str, FT_EXIT) == 0)
		return (4);
    else if (ft_strcmp(str, FT_UNSET) == 0)
		return (5);
    else if (ft_strcmp(str, FT_EXPORT) == 0)
	    return (6);
	return (-1);
}

void	builtin(const t_builtin builtin, t_list *token, t_data *data)
{
	int	saved_fd[2];

	redirect_io(data, saved_fd);
	data->retcode = builtin(token);
	restore_io(saved_fd);
	set_exit_code(data->retcode);
}

void	fork_builtin(const t_builtin builtin, t_list *token, t_data *data)
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