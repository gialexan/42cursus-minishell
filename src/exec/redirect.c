/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:17:02 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/08 15:09:30 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

static t_token *exec_input(t_token *token, t_token *head, t_token *c);
static t_token *exec_output(t_token *token, t_token *head, t_token *c);
static t_token *exec_append(t_token *token, t_token *head, t_token *c);
static t_token *exec_heredoc(t_token *token, t_token *head, t_token *c);

/*
* Prototipagem inicial da função heredoc.
*
* To do:
* Salvar o fd em algum lugar para usar no na hr de executar
* Os textos esritos no here_doc devem expandir se forem variáveis de expansão.
*
* Includes:
* #include <fcntl.h>
* #include <readline/readline.h>
* #include <readline/history.h>
*/

t_token *exec_redirect(t_token *token, t_token *head)
{
	t_token *c;

    if (!token)
        return head;
	c = advanced(&token);
    if (match(type(c), TK_DLESS))
		return (exec_heredoc(token, head, c));
    else if (match(type(c), TK_LESS))
		return (exec_input(token, head, c));
    else if (match(type(c), TK_GREAT))
		return (exec_output(token, head, c));
    else if (match(type(c), TK_DGREAT))
		return (exec_append(token, head, c));
	lstadd_back(&head, c);
	return (exec_redirect(token, head));
}

static t_token *exec_input(t_token *token, t_token *head, t_token *c)
{
	t_token *file;
	
	file = advanced(&token);
	/*
	fd = open(file->lexema, O_RDONLY);
	*/
	lstdelone(c, free);
	lstdelone(file, free);
	return (exec_redirect(token, head));
}

static t_token *exec_heredoc(t_token *token, t_token *head, t_token *c)
{
	int			fd;
	char		*input;
	t_token		*delimiter;

	delimiter = advanced(&token);
	/*
	fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (TRUE)
	{
		input = readline("> ");
		if (!ft_strcmp(input, delimiter->lexema))
			break ;
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
	free(input);
	*/
	lstdelone(c, free);
	lstdelone(delimiter, free);
	return (exec_redirect(token, head));
}

static t_token *exec_output(t_token *token, t_token *head, t_token *c)
{
	int		fd;
	t_token *file;

	file = advanced(&token);
	/*
	fd = open(file->lexema, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	*/
	lstdelone(c, free);
	lstdelone(file, free);
	return (exec_redirect(token, head));
}

static t_token *exec_append(t_token *token, t_token *head, t_token *c)
{
	int		fd;
	t_token *file;
	
	file = advanced(&token);
	/*
	fd = open(file->lexema, O_WRONLY | O_CREAT | O_APPEND, 0644);
	*/
	lstdelone(c, free);
	lstdelone(file, free);
	return (exec_redirect(token, head));
}
