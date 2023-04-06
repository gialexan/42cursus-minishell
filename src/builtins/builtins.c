/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:50:18 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/06 15:31:38 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_builtin(const char *str);
static void	fork_bultin(const t_builtin builtin, t_list *token, t_data *data);

t_bool    exec_builtins(t_list *token, t_data *data)
{
    int index;
	int	saved_fd[2];

    if (!token)
        return (FALSE);
    token->content = expand(token->content);
    index = is_builtin(token->content);
	const t_builtin	builtin[] = {
		&ft_echo,
		&ft_cd,
		&ft_pwd,
		&ft_env,
		&ft_exit,
		&ft_unset,
		&ft_export,
	};
	if (index >= 0 && index <= 7)
	{
		if (data->pipeline)
			fork_bultin(builtin[index], token, data);
		else
		{
			redirect_io(saved_fd, data);
			data->retcode = builtin[index](token);
			restore_io(saved_fd);
		}
		return (TRUE);
	}
	return (FALSE);
}

static int	is_builtin(const char *str)
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

static void	fork_bultin(const t_builtin builtin, t_list *token, t_data *data)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(data->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(data->fd[STDOUT_FILENO], STDOUT_FILENO);
		data->retcode = builtin(token);
		close(data->fd[STDIN_FILENO]);
		close(data->fd[STDOUT_FILENO]);
		msh_clear();
		exit(data->retcode);
	}
	waitpid(pid, NULL, 0);
	if (data->fd[STDIN_FILENO] != STDIN_FILENO)
		close(data->fd[STDIN_FILENO]);
	if (data->fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(data->fd[STDOUT_FILENO]);
}