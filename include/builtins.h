/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:53:43 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/04 10:41:55 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "helper.h"

int ft_env(t_list *token);
int ft_pwd(t_list *token);
int ft_echo(t_list *token);
int ft_unset(t_list *token);
int ft_export(t_list *token);

#endif