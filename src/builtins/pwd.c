/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 21:59:07 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/04 10:15:51 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_pwd(t_list *token)
{
    t_list  *pwd;

    (void)token;
    pwd = search_envp("PWD", *get_envp());
    if (!pwd)
        msh_error("pwd", "Environment variable doesn't exist.", 0);
    else
        ft_putendl_fd(ft_strchr(pwd->content, '=') + 1, STDOUT_FILENO);
    return (EXIT_SUCCESS);
}
