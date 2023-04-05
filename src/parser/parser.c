/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:32:19 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/04 18:46:45 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "helper.h"

static t_cmd	*words(t_list *token, t_cmd *cmd, t_cmd *head);
static t_cmd	*pipes(t_list *token, t_cmd *cmd, t_cmd *head);
static t_cmd	*parser(t_list *token, t_cmd *cmd, t_cmd *head);
static t_cmd	*syntax_error(t_list *token, t_cmd *head, t_list *c);

t_cmd	*syntax_analysis(t_list *token)
{
	if (!token)
		return (NULL);
	else if (is_eof(token))
		return (NULL);
	else if (is_pipe(token))
		return (syntax_error(NULL, NULL, token));
	return (parser(token, cmdnew(), NULL));
}

static t_cmd *parser(t_list *token, t_cmd *cmd, t_cmd *head)
{
	t_list *c;

	if (!head)
		head = cmd;
	c = advanced(&token);
	if (is_redirect(c) || is_word(c) || is_pipe(c))
	{
		ft_lstadd_back(&cmd->token, c);
		if (is_pipe(c))
			return (pipes(token, cmd, head));
		else if (is_word(c))
			return (parser(token, cmd, head));
		return (words(token, cmd, head));
	}
	else if (is_eof(c))
		return (ft_lstdelone(c, free), head);
	return (syntax_error(token, head, c));
}

static	t_cmd *words(t_list *token, t_cmd *cmd, t_cmd *head)
{
	t_list *c;

	c = advanced(&token);
	if (!is_word(c))
		return (syntax_error(token, head, c));
	ft_lstadd_back(&cmd->token, c);
	return (parser(token, cmd, head));
}

static	t_cmd *pipes(t_list *token, t_cmd *cmd, t_cmd *head)
{	
	t_list	*c;
	t_cmd	*node;

	c = advanced(&token);
	if (is_eof(c) || is_pipe(c) || is_error(c))
		return (syntax_error(token, head, c));
	node = addcmd(cmd);
	ft_lstadd_back(&node->token, c);
	if (is_redirect(c))
		return (words(token, node, head));
	return (parser(token, node, head));
}

static t_cmd	*syntax_error(t_list *token, t_cmd *head, t_list *c)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (is_error(c))
	{
		ft_putstr_fd("syntax error unclosed quotes ` ", STDERR_FILENO);
		ft_putstr_fd(c->content, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
		ft_putchar_fd('`', STDERR_FILENO);
		if (is_eof(c))
			ft_putstr_fd("newline", STDERR_FILENO);
		else
			ft_putstr_fd(c->content, STDERR_FILENO);
	}
	ft_putendl_fd("\'", STDERR_FILENO);
	clear_dlst(head, free);
	ft_lstclear(&token, free);
	ft_lstclear(&c, free);
	return (NULL);
}
