/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:17:02 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/17 10:12:02 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
* Prototipagem inicial da função heredoc.
*
* To do:
* Os textos escritos no here_doc devem expandir se forem variáveis de expansão.
*
* Includes:
* #include <fcntl.h>
* #include <readline/readline.h>
* #include <readline/history.h>
*/

t_list *exec_redirect(t_list *token, t_data *data, t_list *head)
{
	t_list *c;

    if (!token)
        return head;     
	else if (data->readpipe == TRUE)
		exec_pipe(token, head, data, NULL);
	c = advanced(&token);
    if (match(type(c), TK_LESS))
		return (exec_input(token, head, data, c));
    else if (match(type(c), TK_GREAT))
		return (exec_output(token, head, data, c));
    else if (match(type(c), TK_DGREAT))
		return (exec_append(token, head, data, c));
	else if (match(type(c), TK_DLESS))
		return (exec_heredoc(token, head, data, c));
	else if (match(type(c), TK_PIPE))
		return (exec_pipe(token, head, data, c));
	ft_lstadd_back(&head, c);
	return (exec_redirect(token, data, head));
}
