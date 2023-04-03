/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:14:05 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/03 18:05:40 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_key(char *str);
static int	valid_string(char *str);
static int	export_error(char *str);
static int	exec_export(t_list *export, int exit);

int	ft_export(t_list *token)
{
	t_list *aux;
	
	//ajustar por aq.
	aux = expandlst(token, NULL);
	if (!aux->next)
		declare_x(*get_envp());
	else
		exec_export(aux->next, EXIT_SUCCESS);
}

static	int    exec_export(t_list *token, int exit)
{
	char	*key;
	t_list	*node;
	int		string;
    int     lenght;

	if (!token)
		return (exit);
	key = get_key(token->content);
	string = valid_string(key);
	if (string)
		exit = string;
	node = search_envp(key, *get_envp());
	if (node && string)
	{
        lenght = ft_strlen(token->content);
		if (ft_strncmp(token->content, node->content, lenght))
			update_envp(token->content, node);
	}
	else if (!string)
		insert_envp(token->content, get_envp());
	free(key);
	return (exec_export(token->next, exit));
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

static int   valid_string(char *str)
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
	return (EXIT_SUCCESS);
}

static int	export_error(char *str)
{
	msh_error("export", str, 0);
    ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}
