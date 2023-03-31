/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:16:59 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/31 11:03:55 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_list *exec_input(t_list *token, t_list *head, t_data *data, t_list *c)
{
	int		fd;
	t_list *file;

	file = advanced(&token);
	fd = open(file->content, O_RDONLY);
	set_redir(data, fd, STDIN_FILENO, file->content);
	ft_lstdelone(c, free);
	ft_lstdelone(file, free);
	return (exec_redirect(token, data, head));
}

t_list *exec_output(t_list *token, t_list *head, t_data *data, t_list *c)
{
	int		fd;
	t_list *file;

	file = advanced(&token);
	fd = open(file->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	set_redir(data, fd, STDOUT_FILENO, file->content);
	ft_lstdelone(c, free);
	ft_lstdelone(file, free);
	return (exec_redirect(token, data, head));
}

t_list *exec_append(t_list *token, t_list *head, t_data *data, t_list *c)
{
	int		fd;
	t_list *file;

	file = advanced(&token);
	fd = open(file->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	set_redir(data, fd, STDOUT_FILENO, file->content);
	ft_lstdelone(c, free);
	ft_lstdelone(file, free);
	return (exec_redirect(token, data, head));
}

t_list *exec_heredoc(t_list *token, t_list *head, t_data *data, t_list *c)
{
	int			fd;
	char		*input;
	t_list		*delimiter;

	delimiter = advanced(&token);
	fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	set_redir(data, fd, STDIN_FILENO, delimiter->content);
	/*
	while (TRUE)
	{
		input = readline("> ");
		if (!ft_strcmp(input, delimiter->content))
			break ;
		ft_putendl_fd(input, fd);
		free(input);
	}
	free(input);
	*/
	close(fd);
	ft_lstdelone(c, free);
	ft_lstdelone(delimiter, free);
	return (exec_redirect(token, data, head));
}

t_list	*exec_pipe(t_list *token, t_list *head, t_data *data, t_list *c)
{
	if (data->fd[STDIN_FILENO] == STDIN_FILENO && data->readpipe)
		set_pipe(data, FALSE, STDIN_FILENO, STDOUT_FILENO);
	else
	{
		if (data->fd[STDOUT_FILENO] == STDOUT_FILENO)
			set_pipe(data, TRUE, STDOUT_FILENO, STDIN_FILENO);
		ft_lstdelone(c, free);
		return (exec_redirect(token, data, head));
	}
	return (NULL);
}
