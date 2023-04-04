/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:53:43 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/04 12:00:38 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "helper.h"

# define MY_CD "cd"
# define MY_ENV "env"
# define MY_PWD "pwd"
# define MY_ECHO "echo"
# define MY_EXIT "exit"
# define MY_UNSET "unset"
# define MY_EXPORT "export"

int ft_env(t_list *token);
int ft_pwd(t_list *token);
int ft_echo(t_list *token);
int ft_unset(t_list *token);
int ft_export(t_list *token);

#endif