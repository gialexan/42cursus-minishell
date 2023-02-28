/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:32:19 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/28 22:22:38 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static t_cmd *syntax_error(t_token *token);
static t_cmd *words(t_token *token, t_cmd *cmd, t_cmd *first);
static t_cmd *pipes(t_token *token, t_cmd *cmd, t_cmd *first);
static t_cmd *parser(t_token *token, t_cmd *cmd, t_cmd *first);

static t_token *advanced(t_token **token)
{
	t_token *current;
	
	current = *token;
	*token = (*token)->next;
	current->next = NULL;
	return (current);
}

t_cmd	*cmdnew()
{
	t_cmd *cmd;
	
	cmd =  malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->list = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *syntax_analysis(t_token *token)
{
	if (token == NULL)
		return (NULL);
	else if (match(type(token), TK_EOF))
		return (NULL);
	else if (match(type(token), TK_PIPE))
		return (syntax_error(token));
	return (parser(token, cmdnew(), NULL));
}

static t_cmd *parser(t_token *token, t_cmd *cmd, t_cmd *head)
{
	t_token *c;

	c = advanced(&token);
	// if (!match(type(c), TK_EOF))
	// 	printf("-> PARSER C syntax: %s\n", c->lexema);
	// else
	// 	printf("-> PARSER C syntax: EOF\n");
	if (!head)
		head = cmd;
	if (match(type(c), TK_GREAT) ||
		match(type(c), TK_DLESS) ||
		match(type(c), TK_DGREAT) ||
		match(type(c), TK_LESS))
	{
		//printf("-> REDIR\n");
		lstadd_back(&cmd->list, c);
		return (words(token, cmd, head));
	}
	else if (match(type(c), TK_WORD))
	{
		//printf("-> WORD\n");
		lstadd_back(&cmd->list, c);
		return (parser(token, cmd, head));
	}
	else if (match(type(c), TK_PIPE))
	{
		free((void *)c->lexema);
		free(c);
		return (pipes(token, cmd, head));
	}
	else if (match(type(c), TK_EOF))
	{
		free((void *)c->lexema);
		free(c);
		return (head);
	}
	return (syntax_error(c));
}

static t_cmd *syntax_error(t_token *token)
{
	dprintf(STDERR_FILENO, "minihell: ");
	if (match(type(token), TK_ERROR))
		dprintf(STDERR_FILENO, "error unclosed quotes %s\n", token->lexema);
	else
	{
		dprintf(STDERR_FILENO, "syntax error near unexpected token ");
		if (match(type(token), TK_EOF))
			dprintf(STDERR_FILENO, "'newline'\n");
		else
			dprintf(STDERR_FILENO, "'%s'\n", token->lexema);
	}
	return (NULL);
}

t_cmd *addnode(t_cmd *cmd)
{
	t_cmd	*next_cmd;

	next_cmd = cmdnew();
	cmd->next = next_cmd;
	return (next_cmd);
}

static	t_cmd *pipes(t_token *token, t_cmd *cmd, t_cmd *head)
{	
	t_cmd	*node;
	t_token *c;

	c = advanced(&token);
	if (match(type(c), TK_EOF) || match(type(c), TK_PIPE))
		return (syntax_error(c));
	node = addnode(cmd);
	if (match(type(c), TK_GREAT) ||
		match(type(c), TK_DLESS) ||
		match(type(c), TK_DGREAT) ||
		match(type(c), TK_LESS))
	{
		//printf("-> FUNC PIPE REDIR syntax: %s\n", c->lexema);
		lstadd_back(&node->list, c);
		return (words(token, cmd, head));
	}
	else
	{
		//printf("-> FUNC PIPES syntax: %s\n", c->lexema);
		lstadd_back(&node->list, c);
		return (parser(token, node, head));
	}
}

static	t_cmd *words(t_token *token, t_cmd *cmd, t_cmd *head)
{
	t_token *c;

	c = advanced(&token);
	if (!match(type(c), TK_WORD))
		return (syntax_error(c));
	printf("-> WORDS  C syntax: %s\n", c->lexema);
	lstadd_back(&cmd->list, c);
	return (parser(token, cmd, head));
}
