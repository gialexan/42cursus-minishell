/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:32:19 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 18:45:30 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <helper.h>

static t_cmd *syntax_error(t_list *token);
static t_cmd *words(t_list *token, t_cmd *cmd, t_cmd *head);
static t_cmd *pipes(t_list *token, t_cmd *cmd, t_cmd *head);
static t_cmd *parser(t_list *token, t_cmd *cmd, t_cmd *head);

t_cmd *syntax_analysis(t_list *token)
{
	if (token == NULL)
		return (NULL);
	else if (is_eof(token))
		return (NULL);
	else if (is_pipe(token))
		return (syntax_error(token));
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
	return (syntax_error(c));
}

static	t_cmd *words(t_list *token, t_cmd *cmd, t_cmd *head)
{
	t_list *c;

	c = advanced(&token);
	if (!is_word(c))
		return (syntax_error(c));
	ft_lstadd_back(&cmd->token, c);
	return (parser(token, cmd, head));
}

static	t_cmd *pipes(t_list *token, t_cmd *cmd, t_cmd *head)
{	
	t_list	*c;
	t_cmd	*node;

	c = advanced(&token);
	if (is_eof(c) || is_pipe(c) || is_error(c))
		return (syntax_error(c));
	node = addnode(cmd);
	ft_lstadd_back(&node->token, c);
	if (is_redirect(c))
		return (words(token, node, head));
	return (parser(token, node, head));
}

static t_cmd *syntax_error(t_list *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (is_error(token))
		show_error("error unclosed quotes ", token->content);
	else
	{
		ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
		ft_putchar_fd('`', STDERR_FILENO);
		if (is_eof(token))
			ft_putstr_fd("newline", STDERR_FILENO);
		else
			ft_putstr_fd(token->content, STDERR_FILENO);
		ft_putendl_fd("\'", STDERR_FILENO);
	}
	return (NULL);
}
