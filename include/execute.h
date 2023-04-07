/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:17:53 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/07 16:06:56 by gialexan         ###   ########.fr       */
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
	int			fdclose;
	t_bool		error;
	t_bool		prev_pipe[2];
	t_bool		pipeline;
}	t_data;

void	execute(t_cmd *root);
int 	*get_exit_code(void);
t_cmd	**get_cmdlst_ref(void);
void	set_exit_code(int code);
void	refresh_data(t_data *data);
void	save_cmdlst_ref(t_cmd *root);
t_bool	exec_nopath(t_list *token, t_data *data);
void	execute_cmdlst(t_cmd *root, t_data *data); 
t_bool	exec_abspath(t_list *token, t_data *data);
t_bool	exec_builtins(t_list *token, t_data *data);
void	set_pipe(t_data *data, t_bool pipeline, int stdfd);
t_bool	exec_execve(t_list *token, t_data *data, t_bool builtin);
t_list *exec_redirect(t_list *token, t_data *data, t_list *head);
void	set_redir(t_data *data, int fd, int stdfd, char *filename);
t_list *exec_pipe(t_list *token, t_list *head, t_data *data, t_list *c);
t_list *exec_input(t_list *token, t_list *head, t_data *data, t_list *c);
t_list *exec_output(t_list *token, t_list *head, t_data *data, t_list *c);
t_list *exec_append(t_list *token, t_list *head, t_data *data, t_list *c);
t_list *exec_heredoc(t_list *token, t_list *head, t_data *data, t_list *c);

#endif