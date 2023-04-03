/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:03:26 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/03 20:00:10 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

t_list **get_envp(void)
{
	static t_list *envp;

	return (&envp);
}

char	***get_path(void)
{
	static char	**path;

	return (&path);
}

t_data	*get_data(void)
{
	static t_data data;

	return(&data);
}
