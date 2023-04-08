/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 21:59:07 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 06:28:01 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_pwd(t_list *token)
{
    char  pwd[PATH_MAX];

    (void)token;
    if (getcwd(pwd, sizeof(pwd)) == NULL)
        msh_error("getcwd()" , "error", 0);
    ft_putendl_fd(pwd, STDOUT_FILENO);
    return (EXIT_SUCCESS);
}
