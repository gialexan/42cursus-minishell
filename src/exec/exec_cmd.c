/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:43:09 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 16:30:29 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtins.h"

static t_bool	spawn_process(char **cmd, t_data *data);

t_bool	exec_abspath(t_list *token, t_data *data)
{
	char **array;

	if (!is_executable(token))
		return (FALSE);
	else
	{
		array = ft_convert_array(token);
		if (!array)
			return (FALSE);
		return (spawn_process(array, data));
	}
}

t_bool	exec_nopath(t_list *token, t_data *data)
{
	char	*aux;
	char	*path;
	char	**array;

	path = find_path(token->content, *get_path());
	if (!path)
		return (FALSE);
	aux = token->content;
	token->content = path;
	array = ft_convert_array(token);
	if (!array)
		return (FALSE);
	free(aux);
	return (spawn_process(array, data));
}

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
			redirect_io(data, saved_fd);
			data->retcode = builtin[index](token);
			restore_io(saved_fd);
		}
		set_exit_code(data->retcode);
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	spawn_process(char **cmd, t_data *data)
{
	int			pid;
	extern char	**environ;

	fork_hook();
	pid = fork();
	if (pid == 0)
	{
		dup2(data->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(data->fd[STDOUT_FILENO], STDOUT_FILENO);
		if (data->fdclose >= 0)
			close (data->fdclose);
		execve(cmd[0], cmd, environ);
		close(data->fd[STDIN_FILENO]);
		close(data->fd[STDOUT_FILENO]);
		exit(EXIT_FAILURE);
	}
	ft_free_split(cmd);
	if (data->fd[STDIN_FILENO] != STDIN_FILENO)
	 	close(data->fd[STDIN_FILENO]);
	if (data->fd[STDOUT_FILENO] != STDOUT_FILENO)
	 	close (data->fd[STDOUT_FILENO]);
	return (TRUE);
}
