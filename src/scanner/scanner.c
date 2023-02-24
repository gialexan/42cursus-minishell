/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:00:04 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/24 20:55:25 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scanner.h>

static	t_token	*lstlast(t_token *lst);
static	t_token	*scan_token(t_scanner *scanner);
static	void	lstadd_back(t_token **lst, t_token *new);

t_token	*lexical_analysis(t_scanner *scanner, t_token *token)
{
	if (scanner->curr > ft_strlen(scanner->cmd)) //if (scanner->curr >= ft_strlen(scanner->cmd) + 1)
		return (token);
	scanner->start = scanner->curr;
	lstadd_back(&token, scan_token(scanner));
	return (lexical_analysis(scanner, token));
}

t_token *make_token(t_scanner *scanner, t_tk_type type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->lexema = ft_substr(scanner->cmd, scanner->start,
			scanner->curr - scanner->start);
	token->tk_type = type;
	token->next = NULL;
	return (token);
}

static t_token *scan_token(t_scanner *scanner)
{
	char	c;

	skip_space(scanner);
	c = advance(scanner);
	if (c == '\0')
		return (make_token(scanner, TK_EOF));
	else if (c == '|')
		return (make_token(scanner, TK_PIPE));
	else if (c == '<')
	{
		if (match(scanner, '<'))
			return (make_token(scanner, TK_DLESS));
		return (make_token(scanner, TK_LESS));	
	}
	else if (c == '>')
	{
		if (match(scanner, '>'))
			return (make_token(scanner, TK_DGREAT));
		return (make_token(scanner, TK_GREAT));
	}
	else
		return (string(scanner, c));
}

static t_token *lstlast(t_token *lst)
{
	if (lst)
		while (lst->next != NULL)
			lst = lst->next;
	return (lst);
}

static void lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = lstlast(*lst);
		tmp->next = new;
	}
}
