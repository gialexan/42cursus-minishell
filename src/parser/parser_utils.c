/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:32:17 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/31 11:04:57 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	match(t_list *token, t_tk_type expected)
{
	return (token->tk_type == expected);
}

t_cmd	*addcmd(t_cmd *cmd)
{
	t_cmd	*next_cmd;

	next_cmd = cmdnew();
	cmd->next = next_cmd;
	return (next_cmd);
}

t_cmd	*cmdnew(void)
{
	t_cmd *cmd;

	cmd =  malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->token = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_list *advanced(t_list **token)
{
	t_list *current;

	current = *token;
	*token = (*token)->next;
	current->next = NULL;
	return (current);
}