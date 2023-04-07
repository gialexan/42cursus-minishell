/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:06:49 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/07 15:59:20 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
* TO DO:
* Preciso executar o heredoc no processo filho.
*/

t_list *exec_redirect(t_list *token, t_data *data, t_list *head)
{
	t_list *c;

    if (!token)
        return head;
	else if (data->pipeline == TRUE)
		exec_pipe(token, head, data, NULL);
	c = advanced(&token);
    if (match(c, TK_LESS))
		return (exec_input(token, head, data, c));
    else if (match(c, TK_GREAT))
		return (exec_output(token, head, data, c));
    else if (match(c, TK_DGREAT))
		return (exec_append(token, head, data, c));
	else if (match(c, TK_DLESS))
		return (exec_heredoc(token, head, data, c));
	else if (match(c, TK_PIPE))
		return (exec_pipe(token, head, data, c));
	ft_lstadd_back(&head, c);
	return (exec_redirect(token, data, head));
}

void set_pipe(t_data *data, t_bool pipeline, int stdfd)
{
    static int ppfd[2] = {-1, -1};
    if (pipeline)
	{
        if (pipe(ppfd) == -1) 
		{
			msh_error("pipe()", "failed", 0);
            exit(EXIT_FAILURE);
        }
        data->fd[STDOUT_FILENO] = ppfd[STDOUT_FILENO];  
		data->fdclose = ppfd[STDIN_FILENO];
    }
	else
	{
        data->fd[STDIN_FILENO] = ppfd[STDIN_FILENO];
		data->fdclose = ppfd[STDOUT_FILENO];
	}
    data->pipeline = pipeline;
}

void	set_redir(t_data *data, int fd, int stdfd, char *filename)
{
	if (fd < 0)
	{
		msh_error(filename, NULL, 0);
		data->retcode = 1;
		data->error = TRUE;
	}
	else
	{
		if (data->fd[stdfd] != stdfd)
			close(data->fd[stdfd]);
		data->fd[stdfd] = fd;
	}
}
