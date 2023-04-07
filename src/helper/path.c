/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:49:25 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/07 16:40:51 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"
#include "execute.h"

static void save_path_ref(char **path);

void    init_arraypath(void)
{
	char	*path;
	t_list	*envp;
	char	*envp_value;
	char	**splited_path;

	envp = search_envp("PATH", *get_envp());
	if (!envp)
		return ;
	envp_value = ft_strchr(envp->content, '=');
	if (!envp_value)
		return ;
	splited_path = ft_split(envp_value + 1, ':');
	// if (!splited_path)
	// 	return(save_path_ref(&envp_value));
	return(save_path_ref(splited_path));
}

char	*find_path(char *cmd, char **paths)
{
	char	*tmp_path;
	char	*full_path;

	if (!paths || !*paths)
	{
		msh_error(cmd, "command not found", 0);
		set_exit_code(127);
		return (NULL);
	}
	tmp_path = ft_strjoin(*paths, "/");
	full_path = ft_strjoin(tmp_path, cmd);
	free(tmp_path);
	if (!access(full_path, X_OK))
		return (full_path);
	free(full_path);
	return (find_path(cmd, ++paths));
}


static void save_path_ref(char **path)
{
	char ***path_ref;

	path_ref = get_path();
    *path_ref = path;
}
