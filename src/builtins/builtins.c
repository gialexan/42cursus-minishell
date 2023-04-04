/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:50:18 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/04 12:56:58 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(const char *str)
{
    int lenght;

	if (!str)
		return (-1);
    lenght = ft_strlen(str);
	if (!strncmp(str, MY_ECHO, lenght))
		return (0);
	else if (!strncmp(str, MY_CD, lenght))
		return (1);
	else if (!strncmp(str, MY_PWD, lenght))
		return (2);
    else if (!strncmp(str, MY_ENV, lenght))
		return (3);
	else if (!strncmp(str, MY_EXIT, lenght))
		return (4);
    else if (!strncmp(str, MY_UNSET, lenght))
		return (5);
    else if (!strncmp(str, MY_EXPORT, lenght))
	    return (6);
	return (-1);
}

void	execute_builtin(t_list *token)
{
    int index;

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