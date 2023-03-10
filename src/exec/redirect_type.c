/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:16:59 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/10 21:03:03 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

t_token *exec_input(t_token *token, t_token *head, t_data *data, t_token *c)
{
	int		fd;
	t_token *file;
	
	file = advanced(&token);
	fd = open(file->lexema, O_RDONLY);
	set_redir(data, fd, STDIN_FILENO, file->lexema);
	lstdelone(c, free);
	lstdelone(file, free);
	return (exec_redirect(token, data, head));
}

t_token *exec_output(t_token *token, t_token *head, t_data *data, t_token *c)
{
	int		fd;
	t_token *file;

	file = advanced(&token);
	fd = open(file->lexema, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	set_redir(data, fd, STDOUT_FILENO, file->lexema);
	lstdelone(c, free);
	lstdelone(file, free);
	return (exec_redirect(token, data, head));
}

t_token *exec_append(t_token *token, t_token *head, t_data *data, t_token *c)
{
	int		fd;
	t_token *file;
	
	file = advanced(&token);
	fd = open(file->lexema, O_WRONLY | O_CREAT | O_APPEND, 0644);
	set_redir(data, fd, STDOUT_FILENO, file->lexema);
	lstdelone(c, free);
	lstdelone(file, free);
	return (exec_redirect(token, data, head));
}

t_token *exec_heredoc(t_token *token, t_token *head, t_data *data, t_token *c)
{
	int			fd;
	char		*input;
	t_token		*delimiter;

	delimiter = advanced(&token);
	fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	set_redir(data, fd, STDIN_FILENO, delimiter->lexema);
	/*
	while (TRUE)
	{
		input = readline("> ");
		if (!ft_strcmp(input, delimiter->lexema))
			break ;
		ft_putendl_fd(input, fd);
		free(input);
	}
	free(input);
	*/
	close(fd);
	lstdelone(c, free);
	lstdelone(delimiter, free);
	return (exec_redirect(token, data, head));
}

t_token	*exec_pipe(t_token *token, t_token *head, t_data *data, t_token *c)
{
	if (data->fd[STDIN_FILENO] == STDIN_FILENO && data->readpipe)
		set_pipe(data, FALSE, STDIN_FILENO, STDOUT_FILENO);
	else
	{
		if (data->fd[STDOUT_FILENO] == STDOUT_FILENO)
			set_pipe(data, TRUE, STDOUT_FILENO, STDIN_FILENO);
		lstdelone(c, free);
		return (exec_redirect(token, data, head));
	}
	return (NULL);
}
