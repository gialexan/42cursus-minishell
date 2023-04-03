/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:49:25 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/03 09:52:15 by gialexan         ###   ########.fr       */
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
	path = ft_strchr(envp->content, '=') + 1;
	splited_path = ft_split(path, ':');
	save_path_ref(splited_path);
}

void    clear_arraypath(void)
{
    char ***path;
    void *tmp;
	
	path = get_path();
	tmp = *path;
    ft_free_split(tmp);
    path = NULL;
}

static void save_path_ref(char **path)
{
	char ***path_ref;

	path_ref = get_path();
    *path_ref = path;
}
