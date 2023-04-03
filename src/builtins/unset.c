/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:12:39 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/03 11:53:55 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset(t_list *token)
{
	if (!token)
		return ;
	delete_envp(token->content, get_envp(), NULL);
	ft_unset(token->next);
}
