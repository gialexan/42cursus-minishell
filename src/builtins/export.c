/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:14:05 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/23 15:38:21 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "helper.h"

static char     *get_key(char *str);
static t_bool   valid_string(char *str);
static t_bool   export_error(char *str);

void    exec_export(char *str)
{
	char	*key;
	t_list	*node;
    int     lenght;
	t_bool	string;

	key = get_key(str);
	string = valid_string(key);
	node = search_envp(key, *get_envp());
	if (node && string)
	{
        lenght = ft_strlen(str);
		if (ft_strncmp(str, node->content, lenght))
			update_envp(str, node);
	}
	else if (string)
		insert_envp(str, get_envp());
	free(key);
}

static char    *get_key(char *str)
{
	char	*key;
	char	*tmp;
    char	*sign;
	size_t	key_length;

	key = ft_strdup(str);
	sign = ft_strchr(str, '=');
    if (!sign)
        return key;
    key_length = sign - str;
    if (key_length == 0)
        return key;
	tmp = key;
	key = ft_substr(str, 0, key_length);
	free(tmp);
	return (key);
}

static t_bool   valid_string(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (export_error(str));
	while (str[++i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (export_error(str));
	}
	return (TRUE);
}

static t_bool	export_error(char *str)
{
	msh_error("export", str, 0);
    ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	return (FALSE);
}
