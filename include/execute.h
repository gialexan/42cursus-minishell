/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:17:53 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/09 23:32:18 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "helper.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_data
{
	int			fd[2];
	int			retcode;
	int			fdclose;
	int			hdoc_fd;
	t_bool		error;
	t_bool		pipeline;
}	t_data;

void	execute(t_cmd *root);
int		*get_exit_code(void);
t_cmd	**get_cmdlst_ref(void);
void	set_exit_code(int code);
void	restore_io(int saved_fd[]);
void	refresh_data(t_data *data);
t_bool	is_executable(t_list *token);
void	save_cmdlst_ref(t_cmd *root);
void	here_doc(t_data *data, char *delimiter);
void	set_pipe(t_data *data, t_bool pipeline);
t_bool	exec_nopath(t_list *token, t_data *data);
void	redirect_io(t_data *data, int saved_fd[]);
void	execute_cmdlst(t_cmd *root, t_data *data);
t_bool	exec_abspath(t_list *token, t_data *data);
t_bool	exec_builtins(t_list *token, t_data *data);
t_bool	exec_execve(t_list *token, t_data *data, t_bool builtin);
t_list	*exec_redirect(t_list *token, t_data *data, t_list *head);
void	set_redir(t_data *data, int fd, int stdfd, char *filename);
t_list	*exec_pipe(t_list *token, t_list *head, t_data *data, t_list *c);
t_list	*exec_input(t_list *token, t_list *head, t_data *data, t_list *c);
t_list	*exec_output(t_list *token, t_list *head, t_data *data, t_list *c);
t_list	*exec_append(t_list *token, t_list *head, t_data *data, t_list *c);
t_list	*exec_heredoc(t_list *token, t_list *head, t_data *data, t_list *c);
void	save_hdoc_ref(t_data *data, t_list *token, t_list *delim, t_list *c);

#endif