/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/07 15:04:01 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define GREEN_PROMPT "\e[m\e[1;32m❯ \e[m"

#define ENOENT 2
#define EACCES 13
#include <unistd.h>

/* TO DO
 * Criar exit
*/

char	*find_path(char *cmd, char **paths)
{
	char	*tmp_path;
	char	*full_path;

	if (!paths)
	{
		msh_error(cmd, "command not found", 0);
		return (NULL);
	}
	tmp_path = ft_strjoin(*paths, "/");
	full_path = ft_strjoin(tmp_path, cmd);
	free(tmp_path);
	if (!access(full_path, X_OK))
		return (full_path);
	free(full_path);
	return (find_path(cmd, ++paths));
}

t_bool	is_abspath(char *path)
{
	if (ft_strchr("./", path[0]) == 0)
		return (FALSE);
	return (TRUE);
}

t_bool	spawn_process(char **cmd, t_data *data)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(data->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(data->fd[STDOUT_FILENO], STDOUT_FILENO);
		if (data->fdclose >= 0)
			close (data->fdclose);
		execve(cmd[0], cmd, NULL);
		close(data->fd[STDIN_FILENO]);
		close(data->fd[STDOUT_FILENO]);
		exit(EXIT_FAILURE);
	}
	if (data->fd[STDIN_FILENO] != STDIN_FILENO)
	 	close(data->fd[STDIN_FILENO]);
	if (data->fd[STDOUT_FILENO] != STDOUT_FILENO)
	 	close (data->fd[STDOUT_FILENO]);
	ft_free_split((void *)cmd);
	cmd = NULL;
	return (TRUE);
}

t_bool	exec_abspath(t_list *token, t_data *data)
{
	char *path;
	char **array;

	path = token->content;
	if (access(path, F_OK))
	{
		msh_error(path, NULL, ENOENT);
		data->retcode = 127;
		return (FALSE);
	}
	else if (access(path, X_OK))
	{
		msh_error(path, NULL, EACCES);
		data->retcode = 126;
		return (FALSE);
	}
	else
	{
		array = ft_convert_array(token);
		if (!array)
			return (FALSE);
		return (spawn_process(array, data));
	}
}

t_bool	exec_nopath(t_list *token, t_data *data)
{
	char	*aux;
	char	*path;
	char	**array;

	path = find_path(token->content, *get_path());
	if (!path)
		return (FALSE);
	aux = token->content;
	token->content = path;
	array = ft_convert_array(token);
	if (!array)
		return (FALSE);
	free(aux);
	return (spawn_process(array, data));
}

t_bool	exec_execve(t_list *token, t_data *data, t_bool builtin)
{
	if (!token || builtin)
		return (FALSE);
	else if (is_abspath(token->content))
		return (exec_abspath(token, data));
	return (exec_nopath(token, data));
}

void	execute_cmdlst(t_cmd *root, t_data *data)   
{
	t_list	*cmd;
	t_bool	execve;
	t_bool 	builtin;

	if (!root)
		return ;
	cmd = exec_redirect(root->token, data, NULL);
	builtin = exec_builtins(cmd, data);
	execve = exec_execve(cmd, data, builtin);
	refresh_data(data);
	set_exit_code(data->retcode);
	ft_lstclear(&cmd, free);
	execute_cmdlst(root->next, data);
	free(root);
	root = NULL;
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
	data.pipeline = FALSE;
	save_cmdlst_ref(root);
	execute_cmdlst(root, &data);
	while (wait(&wstatus) != -1)
		continue ;
}

void	msh_loop(void)
{
	t_cmd		*root;
	t_list		*token;
    t_scanner	scanner;
	char 		*command;

	while (TRUE)
	{
		command = readline(GREEN_PROMPT);
		if (!ft_strncmp(command, "exit", 5))
			break ;
    	scanner = init_scanner(command);
    	token = lexical_analysis(&scanner, NULL);
		root = syntax_analysis(token);
		execute(root);
		free(command);
		command = NULL;
	}
	free(command);
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;

	init_envment(envp, get_envp());
	init_arraypath();
	msh_loop();
	clear_arraypath();
	clear_envment();
}


















/*
EXPORT TEST BASIC:
 char command[] = "export $test carro=moto";
    scanner = init_scanner(command);
    token = lexical_analysis(&scanner, token);
	parser = syntax_analysis(token);
	execute_cmdlst(parser, get_data());

	t_list *tmp = *get_envp();
	
	while(tmp != NULL)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	clear_arraypath();
	ft_lstclear(get_envp(), free);
*/

/*
UNSET TEST BASIC
char command[] = "unset $carro carro";
    scanner = init_scanner(command);
    token = lexical_analysis(&scanner, token);
	parser = syntax_analysis(token);
	execute_cmdlst(parser, get_data());

	delete_envp("carro", get_envp(), NULL);

	tmp = *get_envp();
	while(tmp != NULL)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}

	clear_arraypath();
	ft_lstclear(get_envp(), free);

*/