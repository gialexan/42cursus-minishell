/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:49:25 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/05 13:45:23 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

static void save_path_ref(char **path);

void    init_arraypath(void)
{
	t_list	*envp;
	char	*path;
	char	**splited_path;

	envp = search_envp("PATH", *get_envp());
	path = ft_strchr(envp->content, '=');
	if (!path)
		return ;
	splited_path = ft_split(path + 1, ':');
	save_path_ref(splited_path);
}

static void save_path_ref(char **path)
{
	char ***path_ref;

	path_ref = get_path();
    *path_ref = path;
}
