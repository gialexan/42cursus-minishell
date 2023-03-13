/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:17:53 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 16:34:09 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <helper.h>
# include <fcntl.h>

typedef struct s_data
{
	int			fd[2];
	int			retcode;
	int			count;
	t_bool		error;
	t_bool		readpipe;
}	t_data;

void	set_redir(t_data *data, int fd, int stdfd, char *filename);
t_list *exec_redirect(t_list *token, t_data *data, t_list *head);
void	set_pipe(t_data *data, t_bool readpipe, int stdfd, int fdclose);
t_list *exec_pipe(t_list *tk, t_list *head, t_data *data, t_list *c);
t_list *exec_input(t_list *tk, t_list *head, t_data *data, t_list *c);
t_list *exec_append(t_list *tk, t_list *head, t_data *data, t_list *c);
t_list *exec_output(t_list *tk, t_list *head, t_data *data, t_list *c);
t_list *exec_heredoc(t_list *tk, t_list *head, t_data *data, t_list *c);

#endif