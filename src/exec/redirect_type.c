/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:16:59 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/09 10:37:27 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

t_token *exec_input(t_token *tk, t_token *head, t_execute *exc, t_token *c)
{
	int		fd;
	t_token *file;
	
	file = advanced(&tk);
	fd = open(file->lexema, O_RDONLY);
	set_redirect(exc, fd, STDIN_FILENO, file->lexema);
	lstdelone(c, free);
	lstdelone(file, free);
	return (exec_redirect(tk, exc, head));
}

t_token *exec_heredoc(t_token *tk, t_token *head, t_execute *exc, t_token *c)
{
	int			fd;
	char		*input;
	t_token		*delimiter;

	delimiter = advanced(&tk);
	fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	set_redirect(exc, fd, STDIN_FILENO, NULL);
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
	return (exec_redirect(tk, exc, head));
}

t_token *exec_output(t_token *tk, t_token *head, t_execute *exc, t_token *c)
{
	int		fd;
	t_token *file;

	file = advanced(&tk);
	fd = open(file->lexema, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	set_redirect(exc, fd, STDOUT_FILENO, file->lexema);
	lstdelone(c, free);
	lstdelone(file, free);
	return (exec_redirect(tk, exc, head));
}

t_token *exec_append(t_token *tk, t_token *head, t_execute *exc, t_token *c)
{
	int		fd;
	t_token *file;
	
	file = advanced(&tk);
	fd = open(file->lexema, O_WRONLY | O_CREAT | O_APPEND, 0644);
	set_redirect(exc, fd, STDOUT_FILENO, file->lexema);
	lstdelone(c, free);
	lstdelone(file, free);
	return (exec_redirect(tk, exc, head));
}


void	set_redirect(t_execute *exc, int fd, int stdfd, char *filename)
{
	if (fd < 0)
	{
		exc->retcode = 1;
		exc->error = TRUE;
	}
	else
	{
		if (exc->fd[stdfd] != stdfd)
			close(exc->fd[stdfd]);
		exc->fd[stdfd] = fd;
	}
}
