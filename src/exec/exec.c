/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:43:14 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 04:19:23 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_cmdlst(t_cmd *root, t_data *data)   
{
	t_list	*cmd;
	t_bool 	builtin;

	if (!root)
		return ;
	cmd = exec_redirect(root->token, data, NULL);
	builtin = exec_builtins(cmd, data);
	exec_execve(cmd, data, builtin);
	refresh_data(data);
	ft_lstclear(&cmd, free);
	execute_cmdlst(root->next, data);
	free(root);
	root = NULL;
	cmd = NULL;
}

void	execute(t_cmd *root)
{
	t_data	data;
	int		wstatus;
	
	data.fd[STDIN_FILENO] = STDIN_FILENO;
	data.fd[STDOUT_FILENO] = STDOUT_FILENO;
	data.retcode = *get_exit_code();
	data.error = FALSE;
	data.fdclose = -1;
	data.hdoc_fd = 0;
	data.pipeline = FALSE;
	save_cmdlst_ref(root);
	execute_cmdlst(root, &data);
	while (wait(&wstatus) != -1)
		continue ;
}
