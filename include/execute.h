/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:17:53 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/06 14:16:40 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "helper.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_data
{
	int			fd[2];
	int			retcode;
	int			count;
	t_bool		error;
	t_bool		pipeline;
}	t_data;

int 	*get_exit_code(void);
t_cmd	**get_cmdlst_ref(void);
void	restore_io(int saved[]);
void	set_exit_code(int code);
void	refresh_data(t_data *data);
void	save_cmdlst_ref(t_cmd *root);
void	redirect_io(int saved[], t_data *data);
t_list *exec_redirect(t_list *token, t_data *data, t_list *head);
void	set_redir(t_data *data, int fd, int stdfd, char *filename);
void set_pipe(t_data *data, t_bool pipeline, int stdfd);
t_list *exec_pipe(t_list *token, t_list *head, t_data *data, t_list *c);
t_list *exec_input(t_list *token, t_list *head, t_data *data, t_list *c);
t_list *exec_output(t_list *token, t_list *head, t_data *data, t_list *c);
t_list *exec_append(t_list *token, t_list *head, t_data *data, t_list *c);
t_list *exec_heredoc(t_list *token, t_list *head, t_data *data, t_list *c);

#endif