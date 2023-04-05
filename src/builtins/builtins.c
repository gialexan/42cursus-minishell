/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:50:18 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/05 14:52:01 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_builtin(const char *str);

int	ft_exit(t_list *str)
{
	return  1;
}

void    exec_builtins(t_list *token, t_data *data)
{
    int index;

    if (!token)
        return ;
    token->content = expand(token->content);
    index = is_builtin(token->content);
	const t_builtin	builtin[] = {
		&ft_echo,
		&ft_cd,
		&ft_pwd,
		&ft_env,
		&ft_exit,
		&ft_unset,
		&ft_export,
	};
	if (index >= 0 && index <= 7)
		builtin[index](token);
}

static int	is_builtin(const char *str)
{
    int lenght;

	if (!str)
		return (-1);
    lenght = ft_strlen(str);
	if (!strncmp(str, FT_ECHO, lenght))
		return (0);
	else if (!strncmp(str, FT_CD, lenght))
		return (1);
	else if (!strncmp(str, FT_PWD, lenght))
		return (2);
    else if (!strncmp(str, FT_ENV, lenght))
		return (3);
	else if (!strncmp(str, FT_EXIT, lenght))
		return (4);
    else if (!strncmp(str, FT_UNSET, lenght))
		return (5);
    else if (!strncmp(str, FT_EXPORT, lenght))
	    return (6);
	return (-1);
}
