/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:06:49 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 16:33:16 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

void	set_pipe(t_data *data, t_bool readpipe, int stdfd, int fdclose)
{
	int ppfd[2];

	pipe(ppfd);
	set_redir(data, ppfd[stdfd], stdfd, "pipe");
	close(ppfd[fdclose]);
	data->readpipe = readpipe;
}

void	set_redir(t_data *data, int fd, int stdfd, char *filename)
{
	if (fd < 0)
	{
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
