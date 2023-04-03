/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:12:39 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/03 19:57:39 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(t_list *token)
{
	if (!token)
		return (EXIT_SUCCESS);
	token->content = pathname_expansion(token->content, 0, 0);
	delete_envp(token->content, get_envp(), NULL);
	return (ft_unset(token->next));
}
