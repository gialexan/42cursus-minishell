/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:21:20 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/10 01:35:57 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

#define GREEN_PROMPT "\e[m\e[1;32m❯ \e[m"
#define END_OF_FILE "here-document delimited by end-of-file (wanted `eof')"

static t_bool	check_input(char *input, char *delimiter);
static void		heredoc_loop(t_data * data, char *delimiter);

void	here_doc(t_data *data, char *delimiter)
{
	int pid;

	turnoff_signals();
	pid = fork();
	if (pid == 0)
	{
		set_hdoc_hooks();
		heredoc_loop(data, delimiter);
		if (data->fd[STDIN_FILENO] != STDIN_FILENO)
	 		close(data->fd[STDIN_FILENO]);
		if (data->fd[STDOUT_FILENO] != STDOUT_FILENO)
	 		close (data->fd[STDOUT_FILENO]);
		clear_heredoc();
		close(data->hdoc_fd);
		exit(EXIT_SUCCESS);
	}
	set_interactive_hooks();
    waitpid(pid, NULL, 0);
	close(data->hdoc_fd);
}

void	save_hdoc_ref(t_data * data, t_list *head, t_list *delimiter)
{
	t_hdoc *clean;

	clean = get_clean();
	clean->head = head;
	clean->delimiter = delimiter;
	clean->fd = data->hdoc_fd;
}

static void	heredoc_loop(t_data * data, char *delimiter)
{
	char *input;
	char *expanded;

	while (TRUE)
	{
		input = readline(GREEN_PROMPT);
		if (check_input(input, delimiter))
			break;
		expanded = pathname_expansion(input, 0, 0);
		ft_putendl_fd(expanded, data->hdoc_fd);
		free(expanded);
	}
	free(input);
}

static t_bool  check_input(char *input, char *delimiter)
{
    if (!input)
    {
        msh_error("warning", END_OF_FILE, 0);
        return (TRUE);
    }
    else if (ft_strcmp(input, delimiter) == 0)
        return (TRUE);
    return (FALSE);
}
