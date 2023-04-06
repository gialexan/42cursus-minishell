/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:43:06 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/05 22:43:31 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_cmd	**get_cmdlst_ref(void)
{
	static t_cmd *root;

	return (&root);
}

void	save_cmdlst_ref(t_cmd *root)
{
	t_cmd	**cmd;

	cmd = get_cmdlst_ref();
	*cmd = root;
}