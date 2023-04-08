/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:16:59 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/07 18:25:13 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
	char	*input;
	char	*expanded;
	t_list	*delimiter;

	delimiter = advanced(&token);
	delimiter->content = expand(delimiter->content);
	if (delimiter->content)
	{
		fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		set_redir(data, fd, STDIN_FILENO, delimiter->content);
		while (TRUE)
		{
			input = readline("> ");
			if (!ft_strcmp(input, delimiter->content))
				break ;
			expanded = pathname_expansion(input, 0, 0);
			ft_putendl_fd(expanded, fd);
			free(expanded);
		}
		close(fd);
		free(input);
	}
	ft_lstdelone(c, free);
	ft_lstdelone(delimiter, free);
	return (exec_redirect(token, data, head));
}

t_list	*exec_pipe(t_list *token, t_list *head, t_data *data, t_list *c)
{
	if (data->fd[STDIN_FILENO] == STDIN_FILENO && data->pipeline == TRUE)
		set_pipe(data, FALSE, STDOUT_FILENO);
	else
	{
		if (data->fd[STDOUT_FILENO] == STDOUT_FILENO)
			set_pipe(data, TRUE, STDOUT_FILENO);
		ft_lstdelone(c, free);
		return (exec_redirect(token, data, head));
	}
	return (NULL);
	ft_lstdelone(c, free);
	return (exec_redirect(token, data, head));
}
