/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:32:19 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/07 18:45:28 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static t_token *advanced(t_token **token);
static t_cmd *words(t_token *token, t_cmd *cmd, t_cmd *head);
static t_cmd *pipes(t_token *token, t_cmd *cmd, t_cmd *head);
static t_cmd *parser(t_token *token, t_cmd *cmd, t_cmd *head);

t_cmd *syntax_analysis(t_token *token)
{
	if (token == NULL)
		return (NULL);
	else if (is_eof(token))
		return (NULL);
	else if (is_pipe(token))
		return (syntax_error(token));
	return (parser(token, cmdnew(), NULL));
}

static t_cmd *parser(t_token *token, t_cmd *cmd, t_cmd *head)
{
	t_token *c;

	if (!head)
		head = cmd;
	c = advanced(&token);
	if (is_redirect(c) || is_word(c))
	{
		lstadd_back(&cmd->list, c);
		if (is_word(c))
			return (parser(token, cmd, head));
		return (words(token, cmd, head));
	}
	else if (is_pipe(c) || is_eof(c))
	{
		if (is_eof(c))
			return (lstdelone(c, free), head);
		lstdelone(c, free);
		return (pipes(token, cmd, head));
	}
	return (syntax_error(c));
}

static	t_token *advanced(t_token **token)
{
	t_token *current;

	current = *token;
	*token = (*token)->next;
	current->next = NULL;
	return (current);
}

static	t_cmd *words(t_token *token, t_cmd *cmd, t_cmd *head)
{
	t_token *c;

	c = advanced(&token);
	if (!is_word(c))
		return (syntax_error(c));
	lstadd_back(&cmd->list, c);
	return (parser(token, cmd, head));
}

static	t_cmd *pipes(t_token *token, t_cmd *cmd, t_cmd *head)
{	
	t_token	*c;
	t_cmd	*node;

	c = advanced(&token);
	if (is_eof(c) || is_pipe(c) || is_error(c))
		return (syntax_error(c));
	node = addnode(cmd);
	lstadd_back(&node->list, c);
	if (is_redirect(c))
		return (words(token, node, head));
	return (parser(token, node, head));
}
