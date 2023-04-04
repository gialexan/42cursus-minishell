/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 21:59:07 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/04 10:59:09 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#define PATH_MAX 4096

int ft_pwd(t_list *token)
{
   char  pwd[PATH_MAX];

    (void)token;
    getcwd(pwd, sizeof(pwd));
    if (!pwd)
        msh_error("pwd", "Environment variable doesn't exist.", 0);
    ft_putendl_fd(pwd, STDOUT_FILENO);
    return (EXIT_SUCCESS);
}
