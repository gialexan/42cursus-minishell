/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:17:02 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/07 20:11:51 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <exec.h>

t_token *exec_input(t_token *token, t_token *head, t_token *c);
t_token *exec_output(t_token *token, t_token *head, t_token *c);
t_token *exec_append(t_token *token, t_token *head, t_token *c);
t_token *exec_heredoc(t_token *token, t_token *head, t_token *c);

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

t_token *exec_input(t_token *token, t_token *head, t_token *c)
{
	t_token *filename = advanced(&token);
	lstdelone(c, free);
	lstdelone(filename, free);
	return (exec_redirect(token, head));
}

t_token *exec_heredoc(t_token *token, t_token *head, t_token *c)
{
	t_token *filename = advanced(&token);
	lstdelone(c, free);
	lstdelone(filename, free);
	return (exec_redirect(token, head));
}

t_token *exec_output(t_token *token, t_token *head, t_token *c)
{
	t_token *filename = advanced(&token);
	lstdelone(c, free);
	lstdelone(filename, free);
	return (exec_redirect(token, head));
}

t_token *exec_append(t_token *token, t_token *head, t_token *c)
{
	t_token *filename = advanced(&token);
	lstdelone(c, free);
	lstdelone(filename, free);
	return (exec_redirect(token, head));
}
