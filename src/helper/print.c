/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:01:09 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/08 11:01:50 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <helper.h>

void print(t_token *token)
{
	printf("%8s | %3s | %3s\n", "HEREDOC", token->lexema, token->next->lexema);
}

void	print_stack(t_token *token, int type)
{
	t_token *tmp;

	tmp = token;
	if (type == 1)
	{
		printf("Command:\n\t");
		while(tmp != NULL)
		{
			printf("%s ", tmp->lexema);
			tmp = tmp->next;
		}
		printf("\n");
	}
	else
	{
		while(tmp != NULL)
		{
			printf("TK_TYPE -> %d   |   TK_LEXEMA -> %s\n", tmp->tk_type, tmp->lexema);
			tmp = tmp->next;
		}
	}
}

void	print_cmd(t_cmd *cmd)
{
    t_token *curr_token;
	int count;

	count = 0;
    while (cmd != NULL) {
        printf("Command %d :\n\t", ++count);
        curr_token = cmd->list;
        while (curr_token != NULL) {
            printf("%s ", curr_token->lexema);
            curr_token = curr_token->next;
        }
		printf("\n");
        cmd = cmd->next;
    }
}