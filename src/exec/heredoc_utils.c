/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:21:20 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 02:51:08 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

#define GREEN_PROMPT "\e[m\e[1;32m❯ \e[m"
#define END_OF_FILE "here-document delimited by end-of-file (wanted `eof')"
#define HDOC_FILE "/tmp/heredoc.txt"

static t_bool  check_input(char *input, char *delimiter);
static void		hdoc_loop(t_data * data, char *delimiter);

void	here_doc(t_data *data, char *delimiter)
{
	int pid;
	char *input;
	char *expanded;

	data->hdoc_fd = open(HDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
	{
		set_hdoc_hooks();
		hdoc_loop(data, delimiter);
		close(data->hdoc_fd);
		msh_clear();
		save_and_clean(NULL, NULL, CLEAN);
		exit(EXIT_SUCCESS);
	}
	close(data->hdoc_fd);
    waitpid(pid, NULL, 0);
	set_interactive_hooks();
}

static void	hdoc_loop(t_data * data, char *delimiter)
{
	char *input;
	char *expanded;

	while (TRUE)
	{
		input = readline(GREEN_PROMPT);
		if (check_input(input, delimiter))
			break ;
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
