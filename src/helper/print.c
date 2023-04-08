/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:01:09 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 04:10:01 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

void	print_cmd(t_cmd *cmd)
{
	int		count;
    t_list	*curr_token;

	count = 0;
    while (cmd != NULL)
	{
        printf("Command %d :\n\t", ++count);
        curr_token = cmd->token;
        while (curr_token != NULL)
		{
            printf("%s ", (char *) curr_token->content);
            curr_token = curr_token->next;
        }
		printf("\n");
        cmd = cmd->next;
    }
}

int declare_x(t_list *envp)
{
	if (!envp)
		return (EXIT_SUCCESS);
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putendl_fd(envp->content, STDOUT_FILENO);
	return (declare_x(envp->next));
}
