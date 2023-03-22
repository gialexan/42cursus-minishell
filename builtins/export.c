/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:14:05 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/22 11:29:27 by gialexan         ###   ########.fr       */
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
	char	*tmp;
	t_list	*node;
    int     lenght;
	t_bool	string;

	key = str;
	tmp = get_key(str);
	if (tmp)
		key = tmp;
	string = valid_string(str);
	node = search_envp(key, *get_envp());
	if (node && string)
	{
        lenght = ft_strlen(str);
		if (ft_strncmp(str, node->content, lenght))
		{
			update_envp(str, node);
			free(key);
		}
	}
	else if (string)
		insert_envp(str, get_envp());
}

static char    *get_key(char *str)
{
    char	*sign;
	size_t	key_length;

	sign = ft_strchr(str, '=');
    if (!sign)
        return NULL;
    key_length = sign - str;
    if (key_length == 0)
        return NULL;
    return (ft_substr(str, 0, key_length));
}

static t_bool   valid_string(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (export_error(str));
	while (str[++i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]) && str[i] != '=')
			return (export_error(str));
		else if (str[i] == '=')
			return (TRUE);
	}
	return (TRUE);
}

static t_bool	export_error(char *str)
{
	msh_error("export", str, 0);
    ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	return (FALSE);
}
