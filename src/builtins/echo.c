/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:24:58 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/03 18:17:15 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	write_output(t_list *token);

int	ft_echo(t_list *token)
{
	if (!token->next)
	{
		ft_putstr_fd("\n", 1);
		return (EXIT_SUCCESS);
	}
    advanced(&token);
	if (token && !ft_strncmp(token->content, "-n", 2))
	{
		if (!token->next)
			return (EXIT_SUCCESS);
        while(token && !ft_strncmp(token->content, "-n", 2))
            advanced(&token);
		write_output(token);
	}
	else
	{
		write_output(token);
		ft_putstr_fd("\n", 1);
	}
	return (EXIT_SUCCESS);
}

static void	write_output(t_list *token)
{
    char *tmp;

    if (!token)
        return ;
    tmp = token->content;
    token->content = expandchr(tmp);
	ft_putstr_fd(token->content, 1);
    free(tmp);
	return (write_output(token->next));
}
