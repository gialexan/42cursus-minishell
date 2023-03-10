/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:17:53 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/11 00:14:07 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <helper.h>
# include <fcntl.h>

typedef struct s_redirect
{
	int		fd;
	t_bool	boolean;
}	t_redirect;

typedef struct s_data
{
	int			fd[2];
	int			retcode;
	int			count;
	t_bool		error;
	t_bool		readpipe;
}	t_data;

void	set_redir(t_data *data, int fd, int stdfd, char *filename);
t_token *exec_redirect(t_token *token, t_data *data, t_token *head);
void	set_pipe(t_data *data, t_bool readpipe, int stdfd, int fdclose);
t_token *exec_pipe(t_token *tk, t_token *head, t_data *data, t_token *c);
t_token *exec_input(t_token *tk, t_token *head, t_data *data, t_token *c);
t_token *exec_append(t_token *tk, t_token *head, t_data *data, t_token *c);
t_token *exec_output(t_token *tk, t_token *head, t_data *data, t_token *c);
t_token *exec_heredoc(t_token *tk, t_token *head, t_data *data, t_token *c);

#endif