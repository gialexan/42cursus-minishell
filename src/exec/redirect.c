/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:17:02 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/09 10:34:07 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

static t_token *input(t_token *token, t_token *head, t_execute *exc, t_token *c);
static t_token *append(t_token *token, t_token *head, t_execute *exc, t_token *c);
static t_token *output(t_token *token, t_token *head, t_execute *exc, t_token *c);
static t_token *heredoc(t_token *token, t_token *head, t_execute *exc, t_token *c);

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

t_token *exec_redirect(t_token *token, t_execute *exc, t_token *head)
{
	t_token *c;

    if (!token)
        return head;
	c = advanced(&token);
    if (match(type(c), TK_LESS))
		return (exec_input(token, head, exc, c));
    else if (match(type(c), TK_GREAT))
		return (exec_output(token, head, exc, c));
    else if (match(type(c), TK_DGREAT))
		return (exec_append(token, head, exc, c));
	else if (match(type(c), TK_DLESS))
		return (exec_heredoc(token, head, exc, c));
	lstadd_back(&head, c);
	return (exec_redirect(token, exc, head));
}
