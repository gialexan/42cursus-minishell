/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:53:43 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 17:51:49 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "helper.h"
# include "execute.h"

# define FT_CD "cd"
# define FT_ENV "env"
# define FT_PWD "pwd"
# define FT_ECHO "echo"
# define FT_EXIT "exit"
# define FT_UNSET "unset"
# define FT_EXPORT "export"
# define PATH_MAX 4096

typedef int	(*t_builtin)(t_list *);

int	    ft_exit(t_list *str);
int     ft_cd(t_list *token);
int		is_builtin(char *str);
int     ft_env(t_list *token);
int     ft_pwd(t_list *token);
int     ft_echo(t_list *token);
int     ft_unset(t_list *token);
int     ft_export(t_list *token);
void	builtin(const t_builtin builtin, t_list *token, t_data *data);
void	fork_builtin(const t_builtin builtin, t_list *token, t_data *data);

#endif