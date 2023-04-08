/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:16:59 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 17:38:10 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

#define HDOC_FILE "/tmp/heredoc.txt"

t_list *exec_input(t_list *token, t_list *head, t_data *data, t_list *c)
{
	int		fd;
	t_list	*file;

	file = advanced(&token);
	file->content = expand(file->content);
	if (file->content)
	{	
		fd = open(file->content, O_RDONLY);
		set_redir(data, fd, STDIN_FILENO, file->content);
	}
	ft_lstdelone(c, free);
	ft_lstdelone(file, free);
	return (exec_redirect(token, data, head));
}

t_list *exec_output(t_list *token, t_list *head, t_data *data, t_list *c)
{
	int		fd;
	t_list	*file;

	file = advanced(&token);
	file->content = expand(file->content);
	if (file->content)
	{	
		fd = open(file->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		set_redir(data, fd, STDOUT_FILENO, file->content);
	}
	ft_lstdelone(c, free);
	ft_lstdelone(file, free);
	return (exec_redirect(token, data, head));
}

t_list *exec_append(t_list *token, t_list *head, t_data *data, t_list *c)
{
	int		fd;
	t_list	*file;

	file = advanced(&token);
	file->content = expand(file->content);
	if (file->content)
	{
		fd = open(file->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		set_redir(data, fd, STDOUT_FILENO, file->content);
	}
	ft_lstdelone(c, free);
	ft_lstdelone(file, free);
	return (exec_redirect(token, data, head));
}

t_list *exec_heredoc(t_list *token, t_list *head, t_data *data, t_list *c)
{
	int		fd;
	t_list	*delimiter;

	delimiter = advanced(&token);
	delimiter->content = expand(delimiter->content);
	if (delimiter->content)
	{
		turnoff_signals();
		save_and_clean(token, SAVE_ACTION);
		save_and_clean(delimiter, SAVE_ACTION);
		here_doc(data, delimiter->content);
		if (data->hdoc_fd != 0)
		{
			fd = open(HDOC_FILE, O_RDONLY);
			set_redir(data, fd, STDIN_FILENO, "heredoc");
		}
	}
	ft_lstdelone(c, free);
	ft_lstdelone(delimiter, free);
	return (exec_redirect(token, data, head));
}

t_list	*exec_pipe(t_list *token, t_list *head, t_data *data, t_list *c)
{
	if (data->fd[STDIN_FILENO] == STDIN_FILENO && data->pipeline == TRUE)
		set_pipe(data, FALSE);
	else
	{
		if (data->fd[STDOUT_FILENO] == STDOUT_FILENO)
			set_pipe(data, TRUE);
		ft_lstdelone(c, free);
		return (exec_redirect(token, data, head));
	}
	return (exec_redirect(token, data, head));
}
