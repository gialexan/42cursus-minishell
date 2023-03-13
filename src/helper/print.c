/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:01:09 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 19:32:01 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <helper.h>

void print_redir(t_list *token)
{
	printf("%8s | %3s | %3s\n", "HEREDOC", (char *)token->content, (char *)token->next->content);
}

void	print_stack(t_list *lst, int type)
{
	t_list		*tmp;
	const char	*content;

	tmp = lst;
	if (type == 1)
	{
		printf("Command:\n\t");
		while(tmp != NULL)
		{
			content = tmp->content;
			printf("%s ", content);
			tmp = tmp->next;
		}
		printf("\n");
	}
	else
	{
		while(tmp != NULL)
		{
			content = tmp->content;
			printf("TK_TYPE -> %d   |   TK_LEXEMA -> %s\n", tmp->tk_type, content);
			tmp = tmp->next;
		}
	}
}

void	print_cmd(t_cmd *cmd)
{
    t_list *curr_token;
	int count;

	count = 0;
    while (cmd != NULL) {
        printf("Command %d :\n\t", ++count);
        curr_token = cmd->token;
        while (curr_token != NULL) {
            printf("%s ", (char *) curr_token->content);
            curr_token = curr_token->next;
        }
		printf("\n");
        cmd = cmd->next;
    }
}
