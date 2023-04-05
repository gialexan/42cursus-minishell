/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:11:31 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/05 09:30:11 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#define NO_FILE_OR_DIRECTOR 2

static t_bool	update_pwd(void);
static t_bool	update_oldpwd(void);
static char		*get_key_value(char *key);
static t_bool	change_dir(t_list *token, int size);

int	ft_cd(t_list *token)
{
	int	size;
	size = ft_lstsize(token);
	if (size > 2)
	{
		msh_error("cd", "too many arguments", 0);
		return (EXIT_FAILURE);
	}
	if (!change_dir(token, size))
		return (EXIT_FAILURE);
	if (!update_oldpwd())
		return (EXIT_FAILURE);
	if (!update_pwd())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_bool	change_dir(t_list *token, int size)
{
	char	*path;
	int		result;

	if (size == 1 || !ft_strncmp((token->next->content), "~", 1))
	{
		path = get_key_value("HOME");
		if (chdir(path) == 0)
			return (TRUE);
	}
	path = token->next->content;
	if (!path)
		path = get_key_value("HOME");
	if (chdir(path) == 0)
		return (TRUE);
	msh_error("cd", NULL, NO_FILE_OR_DIRECTOR);
	return (FALSE);
}

static t_bool	update_pwd(void)
{
	t_list	*node;
	char	*tmp;
	char	*get_result;
	char	new_path[PATH_MAX];

	get_result = getcwd(new_path, sizeof(new_path));
	if (!get_result)
		return (FALSE);
	node = search_envp("PWD", *get_envp());
	if (!node)
		return (FALSE);
	tmp = ft_strjoin("PWD=", new_path);
	if (!tmp)
		return (FALSE);
	update_envp(tmp, node);
	free(tmp);
	return (TRUE);
}

static t_bool	update_oldpwd(void)
{
	char	*oldpwd;
	t_list	*node;

	oldpwd = ft_strjoin("OLDPWD=", get_key_value("PWD"));
	if (!oldpwd)
		return (FALSE);
	node = search_envp("OLDPWD", *get_envp());
	if (!node)
		return (FALSE);
	update_envp(oldpwd, node);
	free(oldpwd);
	return (TRUE);
}

static char	*get_key_value(char *key)
{
	t_list	*tmp;
	char	*value;

	tmp = search_envp(key, *get_envp());
	if (!tmp)
		return (NULL);
	value = ft_strchr(tmp->content, '=') + 1;
	return (value);
}
