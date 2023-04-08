/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 21:59:07 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/07 16:47:10 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_pwd(t_list *token)
{
    char  pwd[PATH_MAX];

    (void)token;
    getcwd(pwd, sizeof(pwd));
    ft_putendl_fd(pwd, STDOUT_FILENO);
    return (EXIT_SUCCESS);
}
