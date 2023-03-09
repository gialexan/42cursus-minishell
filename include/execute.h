/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:17:53 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/09 09:53:37 by gialexan         ###   ########.fr       */
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

typedef struct s_excute
{
	int			fd[2];
	int			retcode;
	t_bool		error;
}	t_execute;

t_token *exec_redirect(t_token *token, t_execute *exc, t_token *head);
void	set_redirect(t_execute *exc, int fd, int stdfd, char *filename);
t_token *exec_input(t_token *tk, t_token *head, t_execute *exc, t_token *c);
t_token *exec_append(t_token *tk, t_token *head, t_execute *exc, t_token *c);
t_token *exec_output(t_token *tk, t_token *head, t_execute *exc, t_token *c);
t_token *exec_heredoc(t_token *tk, t_token *head, t_execute *exc, t_token *c);

#endif